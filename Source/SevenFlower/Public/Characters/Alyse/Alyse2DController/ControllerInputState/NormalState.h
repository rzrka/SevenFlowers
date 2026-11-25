// Copyright QueueBitGames

#pragma once

#include "CoreMinimal.h"
#include "Characters/Alyse/Alyse2DController/ControllerInputState/AlyseControllerInputState.h"
#include "Characters/AbilitySystem/SFAbilitySystemComponent.h"
#include "NormalState.generated.h"

/**
 * 
 */
UCLASS()
class SEVENFLOWER_API UNormalState : public UAlyseControllerInputState
{
	GENERATED_BODY()
	
	virtual void InputTagPressed(FGameplayTag InputTag) override;
	
};
