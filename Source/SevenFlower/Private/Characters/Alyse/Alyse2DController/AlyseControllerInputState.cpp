// Copyright QueueBitGames


#include "Characters/Alyse/Alyse2DController/AlyseControllerInputState.h"

#include "Characters/Alyse/Alyse2DController/Alyse2DController.h"

void UAlyseControllerInputState::Initialize(AAlyse2DController* NewController)
{
	Controller = NewController;
}

void UAlyseControllerInputState::ChangeState(TSubclassOf<UAlyseControllerInputState> NewState)
{
	 Controller->ChangeInputState(NewState);
}
