// Copyright QueueBitGames


#include "Characters/Alyse/Alyse2DController/ControllerInputState/NormalState.h"
#include "SFGameplayTags.h"
#include "Characters/Alyse/Alyse2DController/ControllerInputState/AbilityState.h"
#include "Characters/Alyse/Alyse2DController/Alyse2DController.h"
#include "Characters/Alyse/Alyse2DController/ControllerInputState/MovementState.h"
#include "Interaction/lightingInterface.h"

void UNormalState::InputTagPressed(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FSFGameplayTags::Get().InputTag_WeakAttack))
	{
		if (Controller->GetASC())
		{
			Controller->GetASC()->AbilityInputTagPressed(InputTag);
		}
		
		return;
	}
	
	SetStateOnTarget();
	
	Controller->GetCurrentInputState()->InputTagPressed(InputTag);
}

