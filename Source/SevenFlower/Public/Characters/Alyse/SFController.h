// Copyright QueueBitGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SFController.generated.h"

class UDamageTextComponent;
class USFInputConfiguration;
struct FGameplayTag;
struct FInputActionValue;
class UInputAction;
class USFAbilitySystemComponent;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class SEVENFLOWER_API ASFController : public APlayerController
{
	GENERATED_BODY()

public:

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter);
	
protected:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AlyseContext;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> CloseWidgetAction;
	
	virtual void SetupInputComponent() override;
	virtual void Move(const FInputActionValue& InputActionValue);

	virtual void AbilityInputTagPressed(FGameplayTag InputTag);
	virtual void AbilityInputTagReleased(FGameplayTag InputTag);
	virtual void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<USFInputConfiguration> InputConfig;

	UPROPERTY()
	TObjectPtr<USFAbilitySystemComponent> SFAbilitySystemComponent;

	USFAbilitySystemComponent* GetASC();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;

	
};
 