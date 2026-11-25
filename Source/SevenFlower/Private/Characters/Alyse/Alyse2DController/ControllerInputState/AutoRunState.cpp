// Copyright QueueBitGames

#include "Characters/Alyse/Alyse2DController/ControllerInputState/AutoRunState.h"

#include "Characters/Alyse/Alyse2DController/Alyse2DController.h"
#include "Characters/Alyse/Alyse2DController/ControllerInputState/AlyseControllerInputState.h"
#include "Components/SplineComponent.h"
#include "Characters/Alyse/Alyse2DController/ControllerInputState/NormalState.h"
#include "Characters/Alyse/Alyse2DController/ControllerInputState/MovementState.h"
#include "Interaction/lightingInterface.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"


UAutoRunState::UAutoRunState()
{
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void UAutoRunState::InputTagReleased(FGameplayTag InputTag)
{
	const APawn* ControlledPawn = Controller->GetPawn();
	if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(
	this,
	ControlledPawn->GetActorLocation(),
	Controller->Destination
	))
	{
		Spline->ClearSplinePoints();
		
		// Если выбрали точку вне NavMesh области, определяем ближайшую доступную
		if (NavPath->PathPoints.IsEmpty())
		{
			NavPath = GetReachablePointNear();
		}
		
		for (const FVector& PointLoc : NavPath->PathPoints)
		{
			Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
		}
	}
}

void UAutoRunState::InputTagPressed(FGameplayTag InputTag)
{
	if (SetStateOnTarget(InputTag))
	{
		Controller->GetCurrentInputState()->InputTagPressed(InputTag);
	}
}

void UAutoRunState::Tick(float DeltaTime)
{
	AutoRun();
}

UNavigationPath* UAutoRunState::GetReachablePointNear()
{
	const APawn* ControlledPawn = Controller->GetPawn();
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	const FNavAgentProperties& AgentProps = ControlledPawn->GetNavAgentPropertiesRef();
	FNavLocation ProjectedDestination;
	bool bProjected = NavSys->ProjectPointToNavigation(
		Controller->Destination,
		ProjectedDestination,       
		FVector(500.0f, 500.0f, 300.0f),           
		&AgentProps
	);

	Controller->Destination = ProjectedDestination;

	return UNavigationSystemV1::FindPathToLocationSynchronously(
		this,
		ControlledPawn->GetActorLocation(),
		Controller->Destination
	);
}
void UAutoRunState::AutoRun()
{
	if (APawn* ControlledPawn = Controller->GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(
			ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(
			LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);
		
		const float DistanceToDestination = (LocationOnSpline - Controller->Destination).Length();
		
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			ChangeState(UNormalState::StaticClass());
		}
	}
}
