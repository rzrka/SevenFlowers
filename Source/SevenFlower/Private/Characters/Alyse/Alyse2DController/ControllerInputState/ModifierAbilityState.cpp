// Copyright QueueBitGames


#include "Characters/Alyse/Alyse2DController/ControllerInputState/ModifierAbilityState.h"
#include "Characters/Alyse/Alyse2DController/ControllerInputState/AbilityState.h"
#include "Characters/Alyse/Alyse2DController/ControllerInputState/NormalState.h"

#include "Characters/Alyse/Alyse2DController/Alyse2DController.h"

void UModifierAbilityState::InputTagPressed(FGameplayTag InputTag)
{
	if (Controller->GetASC())
	{
		Controller->GetASC()->AbilityInputTagPressed(InputTag);
	}
}

void UModifierAbilityState::InputTagHeld(FGameplayTag InputTag)
{

	if (Controller->GetASC())
	{
		Controller->GetASC()->AbilityInputTagHeld(InputTag);
	}
}

void UModifierAbilityState::InputTagReleased(FGameplayTag InputTag)
{
	if (Controller->GetASC())
	{
		Controller->GetASC()->AbilityInputTagReleased(InputTag);
	}
}

