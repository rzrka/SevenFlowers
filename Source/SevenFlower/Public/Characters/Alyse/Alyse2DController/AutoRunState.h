// Copyright QueueBitGames

#pragma once

#include "CoreMinimal.h"
#include "Characters/Alyse/Alyse2DController/AlyseControllerInputState.h"
#include "AutoRunState.generated.h"

class UNavigationPath;
class USplineComponent;
/**
 * 
 */
UCLASS()
class SEVENFLOWER_API UAutoRunState : public UAlyseControllerInputState
{
	GENERATED_BODY()
	
	UAutoRunState();
	
	virtual void InputTagReleased(FGameplayTag InputTag) override;
	virtual void InputTagPressed(FGameplayTag InputTag) override;
	
	virtual void Tick(float DeltaTime) override;
private:
	UNavigationPath* GetReachablePointNear();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;
	
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;
	
	void AutoRun();
};
