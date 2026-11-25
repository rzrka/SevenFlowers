// Copyright QueueBitGames


#include "Characters/Alyse/Alyse2DController/ControllerInputState/AlyseControllerInputState.h"
#include "Characters/Alyse/Alyse2DController/ControllerInputState/MovementState.h"
#include "Characters/Alyse/Alyse2DController/ControllerInputState/NormalState.h"
#include "SFGameplayTags.h"
#include "Interaction/lightingInterface.h"
#include "Characters/Alyse/Alyse2DController/Alyse2DController.h"


void UAlyseControllerInputState::Initialize(AAlyse2DController* NewController)
{
	Controller = NewController;
}

void UAlyseControllerInputState::ChangeState(TSubclassOf<UAlyseControllerInputState> NewState)
{
	 Controller->ChangeInputState(NewState);
}

bool UAlyseControllerInputState::SetStateOnTarget(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FSFGameplayTags::Get().InputTag_WeakAttack))
	{
		if (Controller->GetASC())
		{
			Controller->GetASC()->AbilityInputTagPressed(InputTag);
		}
		
		return false;
	}
	
	AActor* Target = Controller->GetCursorHit().GetActor();
	
	if (Target && Target->Implements<UlightingInterface>())
	{
		ChangeState(UAbilityState::StaticClass());
	}else
	{
		ChangeState(UMovementState::StaticClass());
	}
	return true;
}
