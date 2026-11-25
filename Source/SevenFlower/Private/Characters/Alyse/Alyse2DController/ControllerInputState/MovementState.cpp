// Copyright QueueBitGames

#include "Characters/Alyse/Alyse2DController/ControllerInputState/MovementState.h"
#include "Characters/Alyse/Alyse2DController/Alyse2DController.h"
#include "Characters/Alyse/Alyse2DController/ControllerInputState/NormalState.h"


#include "Characters/Alyse/Alyse2DController/ControllerInputState/AutoRunState.h"


void UMovementState::InputTagReleased(FGameplayTag InputTag)
{
	ChangeState(UAutoRunState::StaticClass());
	Controller->GetCurrentInputState()->InputTagReleased(InputTag);
	
}

void UMovementState::Move()
{
	if (Controller->GetCursorHit().bBlockingHit)
	{
		Controller->Destination = Controller->GetCursorHit().ImpactPoint;
	}
	if (APawn* Pawn = Controller->GetPawn())
	{
		const FVector Direction = (Controller->Destination - Pawn->GetActorLocation()).GetSafeNormal();
		Pawn->AddMovementInput(Direction);
	}
}

void UMovementState::InputTagPressed(FGameplayTag InputTag)
{
	Move();
}

void UMovementState::InputTagHeld(FGameplayTag InputTag)
{	
	Move();
}



