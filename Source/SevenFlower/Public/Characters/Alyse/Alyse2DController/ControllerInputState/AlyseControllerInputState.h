// Copyright QueueBitGames

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "AlyseControllerInputState.generated.h"

class AAlyse2DController;

/**
 * 
 */
UCLASS()
class SEVENFLOWER_API UAlyseControllerInputState : public UObject
{
	GENERATED_BODY()
	
public:
	
	void Initialize(AAlyse2DController* NewController);
	
	virtual void InputTagPressed(FGameplayTag InputTag) {};
	virtual void InputTagReleased(FGameplayTag InputTag) {};
	virtual void InputTagHeld(FGameplayTag InputTag) {};
	
	virtual void Tick(float DeltaTime) {}
	
	void ChangeState(
		TSubclassOf<UAlyseControllerInputState> NewState	
	);
protected:
	
	UPROPERTY()
	TObjectPtr<AAlyse2DController> Controller;
	
	bool SetStateOnTarget(FGameplayTag InputTag);
	

};
