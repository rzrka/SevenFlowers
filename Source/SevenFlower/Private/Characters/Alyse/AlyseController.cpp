// Copyright QueueBitGames

#include "Characters/Alyse/AlyseController.h"
#include "Characters/Alyse/AlyseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Input/SFInputComponent.h"

AAlyseController::AAlyseController()
{
	bReplicates = true;
}

void AAlyseController::BeginPlay()
{
	Super::BeginPlay();
	check(AlyseContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(AlyseContext, 0);
	}
}

void AAlyseController::SetupInputComponent()
{
	Super::SetupInputComponent();

	USFInputComponent* SFInputComponent = CastChecked<USFInputComponent>(InputComponent);
	
	SFInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAlyseController::Look);
	SFInputComponent->BindAction(WalkAction, ETriggerEvent::Triggered, this, &AAlyseController::Walk);
	SFInputComponent->BindAction(WalkAction, ETriggerEvent::Completed, this, &AAlyseController::Walk);
	SFInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AAlyseController::Crouch);
	SFInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AAlyseController::Crouch);
	SFInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AAlyseController::Jump);
}



void AAlyseController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisValue = InputActionValue.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(LookAxisValue.X);
		ControlledPawn->AddControllerPitchInput(LookAxisValue.Y);
	}
}

void AAlyseController::Walk(const FInputActionValue& InputActionValue)
{

	const bool bIsPressed = InputActionValue.Get<bool>();

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (AAlyseCharacter* ControlledCharacter = Cast<AAlyseCharacter>(ControlledPawn))
		{
			if (UCharacterMovementComponent* Movement = ControlledCharacter->GetCharacterMovement())
			{
				Movement->MaxWalkSpeed = bIsPressed ? ControlledCharacter->WalkSpeed : ControlledCharacter->RunSpeed;
			}
		}
	}
}

void AAlyseController::Crouch(const FInputActionValue& InputActionValue)
{
	const bool bIsPressed = InputActionValue.Get<bool>();
	
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (AAlyseCharacter* ControlledCharacter = Cast<AAlyseCharacter>(ControlledPawn))
		{
			if (bIsPressed)
			{
				// TODO подобрать корректные значения
				ControlledCharacter->GetCapsuleComponent()->SetCapsuleHalfHeight(50.f);
				ControlledCharacter->Crouch();
				ControlledCharacter->isCrouching = true;
			}
			else
			{
				ControlledCharacter->GetCapsuleComponent()->SetCapsuleHalfHeight(100.f);
				ControlledCharacter->UnCrouch();
				ControlledCharacter->isCrouching = false;
			}
		}
	}
}

void AAlyseController::Jump(const FInputActionValue& InputActionValue)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (AAlyseCharacter* ControlledCharacter = Cast<AAlyseCharacter>(ControlledPawn))
		{
			ControlledCharacter->Jump();
		}
	}
}
