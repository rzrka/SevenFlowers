// Copyright QueueBitGames


#include "Characters/Alyse/Alyse2DController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "SFGameplayTags.h"
#include "Characters/AbilitySystem/SFAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
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
}

void AAlyse2DController::BeginPlay()
{
	Super::BeginPlay();
	check(AlyseContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
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

void AAlyse2DController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FSFGameplayTags::Get().InputTag_WeakAttack))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}

	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			CachedDestination = Hit.ImpactPoint;
		}

		if (APawn * ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

void AAlyse2DController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IlightingInterface>(CursorHit.GetActor());


	if (LastActor == nullptr and ThisActor == nullptr)
	{
		return; 
	}
	else if (LastActor == nullptr and ThisActor != nullptr)
	{
		ThisActor->HighlightActor();
	}
	else if (LastActor != nullptr and ThisActor == nullptr)
	{
		LastActor->UnHighlightActor();
	}
	else if (LastActor != nullptr and ThisActor != nullptr and LastActor != ThisActor)
	{
		LastActor->UnHighlightActor();
		ThisActor->HighlightActor();
	}
	else if (LastActor != nullptr and ThisActor != nullptr and LastActor == ThisActor)
	{
		return;
	}
}
