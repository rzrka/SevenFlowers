// Copyright QueueBitGames


#include "Characters/Alyse/SFController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "Characters/AbilitySystem/SFAbilitySystemComponent.h"
#include "Input/SFInputComponent.h"
#include "GameFramework/Character.h"
#include "UI/Widgets/DamageTextComponent.h"

void ASFController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter)
{
	if (IsValid(TargetCharacter) && DamageTextComponentClass)
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount);
	}
}

void ASFController::SetupInputComponent()
{
	Super::SetupInputComponent();

	USFInputComponent* SFInputComponent = CastChecked<USFInputComponent>(InputComponent);

	SFInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASFController::Move);

	SFInputComponent->BindAbilityActions(
		InputConfig,
		this,
		&ThisClass::AbilityInputTagPressed,
		&ThisClass::AbilityInputTagReleased,
		&ThisClass::AbilityInputTagHeld
		);
}

void ASFController::Move(const FInputActionValue& InputActionValue)
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

void ASFController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	// GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
}

void ASFController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	
	GetASC()->AbilityInputTagReleased(InputTag);
}

void ASFController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	
	GetASC()->AbilityInputTagHeld(InputTag);
}

USFAbilitySystemComponent* ASFController::GetASC()
{
	if (SFAbilitySystemComponent == nullptr)
	{
		SFAbilitySystemComponent = Cast<USFAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>())); 
	}
	return SFAbilitySystemComponent;
}
