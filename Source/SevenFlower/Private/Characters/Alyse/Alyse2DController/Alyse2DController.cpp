// Copyright QueueBitGames


#include "Characters/Alyse/Alyse2DController/Alyse2DController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "SFGameplayTags.h"
#include "Characters/AbilitySystem/SFAbilitySystemComponent.h"
#include "Characters/Alyse/AlyseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Characters/Alyse/Alyse2DController/AbilityState.h"
#include "Characters/Alyse/Alyse2DController/MovementState.h"
#include "Characters/Alyse/Alyse2DController/NormalState.h"
#include "Input/SFInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interaction/lightingInterface.h"
#include "Characters/Alyse/Alyse2DController/NormalState.h"
#include "GameFramework/MovementComponent.h"

AAlyse2DController::AAlyse2DController()
{
	bReplicates = true;
}

void AAlyse2DController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	if (CurrentInputState)
	{
		CurrentInputState->Tick(DeltaTime);
	}
}

void AAlyse2DController::BeginPlay()
{
	Super::BeginPlay();
	check(AlyseContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(AlyseContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	ChangeInputState(UNormalState::StaticClass());
}

void AAlyse2DController::SetupInputComponent()
{
	Super::SetupInputComponent();

	USFInputComponent* SFInputComponent = CastChecked<USFInputComponent>(InputComponent);

	SFInputComponent->BindAction(ModifierAction, ETriggerEvent::Started, this, &AAlyse2DController::ModifierPressed);
	SFInputComponent->BindAction(ModifierAction, ETriggerEvent::Completed, this, &AAlyse2DController::ModifierReleased);
}


void AAlyse2DController::OnPossess(APawn* ControlledPawn)
{
	Super::OnPossess(ControlledPawn);

	SetSpringArm();
}

void AAlyse2DController::ChangeInputState(TSubclassOf<UAlyseControllerInputState> NewStateClass)
{
	if (!NewStateClass) return;
	
	CurrentInputState = NewObject<UAlyseControllerInputState>(
		this, 
		NewStateClass	
	);
	CurrentInputState->Initialize(this);
	
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("New State: %s"),
		*CurrentInputState->GetClass()->GetName()
	);
}


void AAlyse2DController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	Super::AbilityInputTagPressed(InputTag);
	
	CurrentInputState->InputTagPressed(InputTag);
}

void AAlyse2DController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	CurrentInputState->InputTagReleased(InputTag);
}


void AAlyse2DController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	CurrentInputState->InputTagHeld(InputTag);
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
