// Copyright QueueBitGames

#pragma once

#include "CoreMinimal.h"
#include "Characters/Alyse/Alyse2DController/AbilityState.h"
#include "ModifierAbilityState.generated.h"

/**
 * 
 */
UCLASS()
class SEVENFLOWER_API UModifierAbilityState : public UAbilityState
{
	GENERATED_BODY()
	
	virtual void InputTagPressed(FGameplayTag InputTag) override;
	virtual void InputTagHeld(FGameplayTag InputTag) override;
	virtual void InputTagReleased(FGameplayTag InputTag) override;
};
