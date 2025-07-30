// Copyright QueueBitGames


#include "Input/SFInputConfiguration.h"

const UInputAction* USFInputConfiguration::FindAbilityActionForTag(const FGameplayTag& FGameplayTag) const
{
	const FSFInputAction* Action = AbilityInputActions.Find(FGameplayTag);

	if (!Action or !Action->InputAction)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]."), *FGameplayTag.ToString(), *GetNameSafe(this))
	}
	
	return Action->InputAction;
}
