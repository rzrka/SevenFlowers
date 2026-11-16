// Copyright QueueBitGames


#include "Characters/Alyse/Alyse2DController/AbilityState.h"
#include "Characters/Alyse/Alyse2DController/NormalState.h"
#include "SFGameplayTags.h"

#include "Characters/Alyse/Alyse2DController/Alyse2DController.h"


void UAbilityState::InputTagReleased(FGameplayTag InputTag)
{

	if (Controller->GetASC())
	{
		Controller->GetASC()->AbilityInputTagReleased(InputTag);
	}

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
		Controller->GetASC()->AbilityInputTagHeld(InputTag);
	}

	ChangeState(UNormalState::StaticClass());
}
