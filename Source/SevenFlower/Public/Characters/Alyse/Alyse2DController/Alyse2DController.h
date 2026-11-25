// Copyright QueueBitGames

#pragma once

#include "CoreMinimal.h"
#include "Characters/Alyse/Alyse2DController/ControllerInputState/AbilityState.h"
#include "Characters/Alyse/Alyse2DController/ControllerInputState/NormalState.h"
#include "Characters/Alyse/Alyse2DController/ControllerInputState/AlyseControllerInputState.h"
#include "Characters/Alyse/Alyse2DController/ControllerInputState/ModifierAbilityState.h"
#include "Characters/Alyse/SFController.h"
#include "GameFramework/PlayerController.h"
#include "Alyse2DController.generated.h"


class USplineComponent;
struct FInputActionValue;
class UNavigationPath;
class UAlyseControllerInputState;

class IlightingInterface;
/**
 * 
 */
UCLASS()
class SEVENFLOWER_API AAlyse2DController : public ASFController
{
	GENERATED_BODY()

public:
	AAlyse2DController();
	virtual void PlayerTick(float DeltaTime) override;
	
	FVector Destination = FVector::ZeroVector;
	FHitResult GetCursorHit() const {return CursorHit; }
	UAlyseControllerInputState* GetCurrentInputState() const { return CurrentInputState; }
	
	IlightingInterface* GetThisActor() const {return ThisActor; }
	
	void ChangeInputState(TSubclassOf<UAlyseControllerInputState> NewStateClass);
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* NewPawn) override;
	
	
	UPROPERTY(Transient)
	TObjectPtr<UAlyseControllerInputState> CurrentInputState;
	
	

private:
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<class UInputAction> ModifierAction;
	
	void ModifierPressed(const FInputActionValue& InputActionValue) { ChangeInputState(UModifierAbilityState::StaticClass()); };
	void ModifierReleased(const FInputActionValue& InputActionValue) { ChangeInputState(UNormalState::StaticClass()); };
	
	virtual void AbilityInputTagPressed(FGameplayTag InputTag) override;
	virtual void AbilityInputTagReleased(FGameplayTag InputTag) override;
	virtual void AbilityInputTagHeld(FGameplayTag InputTag) override;

	void CursorTrace();
	IlightingInterface* LastActor;
	IlightingInterface* ThisActor;
	FHitResult CursorHit;
	

	void SetSpringArm();
	
};

