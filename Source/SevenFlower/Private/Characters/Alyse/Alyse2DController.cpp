// Copyright QueueBitGames


#include "Characters/Alyse/Alyse2DController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "SFGameplayTags.h"
#include "Characters/AbilitySystem/SFAbilitySystemComponent.h"
#include "Characters/Alyse/AlyseCharacter.h"
#include "Components/SplineComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Input/SFInputComponent.h"
#include "Interaction/lightingInterface.h"

AAlyse2DController::AAlyse2DController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAlyse2DController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	AutoRun();
}

void AAlyse2DController::BeginPlay()
{
	Super::BeginPlay();
	check(AlyseContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AlyseContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAlyse2DController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AAlyse2DController::OnPossess(APawn* ControlledPawn)
{
	Super::OnPossess(ControlledPawn);

	SetSpringArm();
}


void AAlyse2DController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	Super::AbilityInputTagPressed(InputTag);

	// TODO добавить отдельный тэг для передвижения или переименновать существующие
	if (InputTag.MatchesTagExact(FSFGameplayTags::Get().InputTag_WeakAttack))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

void AAlyse2DController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FSFGameplayTags::Get().InputTag_WeakAttack))
	{
		if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
		return;
	}

	if (bTargeting)
	{
		if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
	}
	else
	{
		const APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(
				this,
				ControlledPawn->GetActorLocation(),
				CachedDestination
			))
			{
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
				}
				TArray x = NavPath->PathPoints;
				if (!NavPath->PathPoints.IsEmpty()) CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() -
					1];
				bAutoRunning = true;
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AAlyse2DController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FSFGameplayTags::Get().InputTag_WeakAttack))
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}

	if (bTargeting)
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		if (CursorHit.bBlockingHit)
		{
			CachedDestination = CursorHit.ImpactPoint;
		}

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

void AAlyse2DController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IlightingInterface>(CursorHit.GetActor());


	if (LastActor != ThisActor)
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->HighlightActor();
	}
}

void AAlyse2DController::SetSpringArm()
{
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;

	AAlyseCharacter* AlyseCharacter = Cast<AAlyseCharacter>(ControlledPawn);
	if (!AlyseCharacter) return;

	USpringArmComponent* SpringArm = AlyseCharacter->FindComponentByClass<USpringArmComponent>();
	if (!SpringArm) return;

	UCameraComponent* Camera = Cast<UCameraComponent>(SpringArm->GetChildComponent(0));
	if (!Camera) return;

	Camera->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));
	Camera->SetRelativeLocation(FVector(0.f, 0.f, 500.f));
}

void AAlyse2DController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(
			ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(
			LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}
