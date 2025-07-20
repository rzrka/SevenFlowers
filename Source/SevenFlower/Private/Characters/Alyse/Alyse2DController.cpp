// Copyright QueueBitGames


#include "Characters/Alyse/Alyse2DController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/lightingInterface.h"

AAlyse2DController::AAlyse2DController()
{
	bReplicates = true;
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

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAlyse2DController::Move);
}

void AAlyse2DController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
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
