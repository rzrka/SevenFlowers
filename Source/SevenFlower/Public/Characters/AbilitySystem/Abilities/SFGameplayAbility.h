// Copyright QueueBitGames

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SFGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class SEVENFLOWER_API USFGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Damage")
	FScalableFloat Damage;
};
