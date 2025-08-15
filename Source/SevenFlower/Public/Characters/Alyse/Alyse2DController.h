// Copyright QueueBitGames

#pragma once

#include "CoreMinimal.h"
#include "SFController.h"
#include "GameFramework/PlayerController.h"
#include "Alyse2DController.generated.h"


class USplineComponent;
struct FInputActionValue;
class UNavigationPath;

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

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* NewPawn) override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<class UInputMappingContext> AlyseContext;


	virtual void AbilityInputTagPressed(FGameplayTag InputTag) override;
	virtual void AbilityInputTagReleased(FGameplayTag InputTag) override;
	virtual void AbilityInputTagHeld(FGameplayTag InputTag) override;

	void CursorTrace();
	IlightingInterface* LastActor;
	IlightingInterface* ThisActor;
	FHitResult CursorHit;

	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = true;

	UNavigationPath* GetReachablePointNear();

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	void SetSpringArm();

	void AutoRun();
};
