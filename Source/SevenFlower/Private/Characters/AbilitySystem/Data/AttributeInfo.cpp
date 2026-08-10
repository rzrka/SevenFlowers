// Copyright QueueBitGames


#include "Characters/AbilitySystem/Data/AttributeInfo.h"

FSFAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag) const
{
	if (const FSFAttributeInfo* Info = AttributeInformation.Find(AttributeTag))
	{
		return *Info;
	}
	
	
	UE_LOG(LogTemp, Warning, TEXT("Can't find Info for AttributeTag [%s], on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this))

	return FSFAttributeInfo();
}
