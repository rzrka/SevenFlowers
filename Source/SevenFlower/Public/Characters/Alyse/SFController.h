// Copyright QueueBitGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SFController.generated.h"

class USFInputConfiguration;
struct FGameplayTag;
struct FInputActionValue;
class USFAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class SEVENFLOWER_API ASFController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<class UInputAction> MoveAction;
	
	virtual void SetupInputComponent() override;
	virtual void Move(const FInputActionValue& InputActionValue);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<USFInputConfiguration> InputConfig;

	UPROPERTY()
	TObjectPtr<USFAbilitySystemComponent> SFAbilitySystemComponent;

	USFAbilitySystemComponent* GetASC();
};
