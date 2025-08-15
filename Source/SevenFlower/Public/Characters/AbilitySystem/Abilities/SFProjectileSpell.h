// Copyright QueueBitGames

#pragma once

#include "CoreMinimal.h"
#include "Characters/AbilitySystem/Abilities/SFGameplayAbility.h"
#include "SFProjectileSpell.generated.h"

class ASFProjectile;
/**
 * 
 */
UCLASS()
class SEVENFLOWER_API USFProjectileSpell : public USFGameplayAbility
{
	GENERATED_BODY()

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ASFProjectile> ProjectileClass;
};
