// Copyright QueueBitGames

#pragma once

#include "Characters/AbilitySystem/SFAbilitySystemComponent.h"
#include "Characters/Alyse/Alyse2DController/AlyseControllerInputState.h"
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AbilityState.generated.h"

/**
 * 
 */
UCLASS()
class SEVENFLOWER_API UAbilityState : public UAlyseControllerInputState
{
	GENERATED_BODY()
	
	virtual void InputTagPressed(FGameplayTag InputTag) override;
	virtual void InputTagReleased(FGameplayTag InputTag) override;
	virtual void InputTagHeld(FGameplayTag InputTag) override;
};
