// Copyright QueueBitGames

#pragma once

#include "CoreMinimal.h"
#include "SFController.h"
#include "GameFramework/PlayerController.h"
#include "AlyseController.generated.h"


struct FInputActionValue;
class UInputAction;
/**
 * 
 */
UCLASS()
class SEVENFLOWER_API AAlyseController : public ASFController
{
	GENERATED_BODY()
public:
	AAlyseController();

	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> WalkAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> JumpAction;
	
	void Look(const FInputActionValue& InputActionValue);
	void Walk(const FInputActionValue& InputActionValue);
	void Crouch(const FInputActionValue& InputActionValue);
	void Jump(const FInputActionValue& InputActionValue);
};
