// Copyright QueueBitGames


#include "Characters/Alyse/Alyse2DController/ControllerInputState/AlyseControllerInputState.h"

#include "Interaction/lightingInterface.h"
#include "Characters/Alyse/Alyse2DController/Alyse2DController.h"
#include "Characters/Alyse/Alyse2DController/ControllerInputState/MovementState.h"

void UAlyseControllerInputState::Initialize(AAlyse2DController* NewController)
{
	Controller = NewController;
}

void UAlyseControllerInputState::ChangeState(TSubclassOf<UAlyseControllerInputState> NewState)
{
	 Controller->ChangeInputState(NewState);
}

void UAlyseControllerInputState::SetStateOnTarget()
{
	AActor* Target = Controller->GetCursorHit().GetActor();
	
	if (Target && Target->Implements<UlightingInterface>())
	{
		ChangeState(UAbilityState::StaticClass());
	}else
	{
		ChangeState(UMovementState::StaticClass());
	}
}
