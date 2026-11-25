// Copyright QueueBitGames


#include "Characters/Alyse/Alyse2DController/AbilityState.h"
#include "Characters/Alyse/Alyse2DController/NormalState.h"
#include "Characters/Alyse/Alyse2DController/MovementState.h"
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
	// if (InputTag.MatchesTagExact(FSFGameplayTags::Get().InputTag_WeakAttack))
	// {
	// 	if (Controller->GetASC() and Controller->GetThisActor())
	// 	{
	// 		Controller->GetASC()->AbilityInputTagPressed(InputTag);
	// 	}
	// 	else
	// 	{
	// 		ChangeState(UMovementState::StaticClass());
	// 	}
	// }
	
	if (Controller->GetASC())
	{
		Controller->GetASC()->AbilityInputTagPressed(InputTag);
	}

	ChangeState(UNormalState::StaticClass());
}
