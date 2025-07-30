// Copyright QueueBitGames

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "SFInputConfiguration.generated.h"

USTRUCT(BlueprintType)
struct FSFInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};
/**
 * 
 */
UCLASS()
class SEVENFLOWER_API USFInputConfiguration : public UDataAsset
{
	GENERATED_BODY()
	
public:

	const UInputAction* FindAbilityActionForTag(const FGameplayTag& InputTag) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FGameplayTag, FSFInputAction> AbilityInputActions;
};
