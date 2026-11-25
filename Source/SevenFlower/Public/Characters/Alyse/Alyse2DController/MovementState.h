// Copyright QueueBitGames

#pragma once

#include "CoreMinimal.h"
#include "Characters/Alyse/Alyse2DController/AlyseControllerInputState.h"
#include "Characters/AbilitySystem/SFAbilitySystemComponent.h"
#include "MovementState.generated.h"


class USplineComponent;
/**
 * 
 */
UCLASS()
class SEVENFLOWER_API UMovementState : public UAlyseControllerInputState
{
	GENERATED_BODY()
	
	
	virtual void InputTagPressed(FGameplayTag InputTag) override;
	virtual void InputTagHeld(FGameplayTag InputTag) override;
	virtual void InputTagReleased(FGameplayTag InputTag) override;
	
	
protected:
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	void Move();
};
