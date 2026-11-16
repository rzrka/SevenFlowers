// Copyright QueueBitGames

#pragma once

#include "CoreMinimal.h"
#include "AlyseControllerInputState.h"
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

	void ModifierPressed() { bModifierKeyDown = true;};
	void ModifierReleased() { bModifierKeyDown = false;};
	bool bModifierKeyDown = false;

	virtual void AbilityInputTagPressed(FGameplayTag InputTag) override;
	virtual void AbilityInputTagReleased(FGameplayTag InputTag) override;
	virtual void AbilityInputTagHeld(FGameplayTag InputTag) override;

	void CursorTrace();
	IlightingInterface* LastActor;
	IlightingInterface* ThisActor;
	FHitResult CursorHit;
	

	void SetSpringArm();
	
};

