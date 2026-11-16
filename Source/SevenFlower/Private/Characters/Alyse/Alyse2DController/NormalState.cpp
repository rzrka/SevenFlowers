// Copyright QueueBitGames


#include "Characters/Alyse/Alyse2DController/NormalState.h"
#include "SFGameplayTags.h"
#include "Characters/Alyse/Alyse2DController/AbilityState.h"
#include "Characters/Alyse/Alyse2DController/Alyse2DController.h"
#include "Characters/Alyse/Alyse2DController/MovementState.h"
#include "Interaction/lightingInterface.h"

void UNormalState::InputTagPressed(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FSFGameplayTags::Get().InputTag_WeakAttack))
	{
		if (Controller->GetASC())
		{
			Controller->GetASC()->AbilityInputTagReleased(InputTag);
		}
		
		return;
	}
	
	AActor* Target = Controller->GetCursorHit().GetActor();
	
	if (Target && Target->Implements<UlightingInterface>())
	{
		ChangeState(UAbilityState::StaticClass());
	}else
	{
		ChangeState(UMovementState::StaticClass());
	}
	
	Controller->GetCurrentInputState()->InputTagPressed(InputTag);
}

