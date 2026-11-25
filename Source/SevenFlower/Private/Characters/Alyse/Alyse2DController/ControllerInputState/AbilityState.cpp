// Copyright QueueBitGames


#include "Characters/Alyse/Alyse2DController/ControllerInputState/AbilityState.h"
#include "Characters/Alyse/Alyse2DController/ControllerInputState/NormalState.h"
#include "Characters/Alyse/Alyse2DController/ControllerInputState/MovementState.h"
#include "SFGameplayTags.h"

#include "Characters/Alyse/Alyse2DController/Alyse2DController.h"


void UAbilityState::InputTagReleased(FGameplayTag InputTag)
{
	ChangeState(UNormalState::StaticClass());
}

void UAbilityState::InputTagHeld(FGameplayTag InputTag)
{

	if (Controller->GetASC())
	{
		Controller->GetASC()->AbilityInputTagHeld(InputTag);
	}

	ChangeState(UNormalState::StaticClass());
}

void UAbilityState::InputTagPressed(FGameplayTag InputTag)
{
	if (Controller->GetASC())
	{
		Controller->GetASC()->AbilityInputTagPressed(InputTag);
	}

	ChangeState(UNormalState::StaticClass());
}
