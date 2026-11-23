// Copyright QueueBitGames

#include "Characters/Alyse/Alyse2DController/Alyse2DController.h"
#include "Characters/Alyse/Alyse2DController/MovementState.h"
#include "Characters/Alyse/Alyse2DController/NormalState.h"


#include "Characters/Alyse/Alyse2DController/AutoRunState.h"


void UMovementState::InputTagReleased(FGameplayTag InputTag)
{
	ChangeState(UAutoRunState::StaticClass());
	Controller->GetCurrentInputState()->InputTagReleased(InputTag);
	
}

void UMovementState::InputTagHeld(FGameplayTag InputTag)
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

