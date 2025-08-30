// Copyright QueueBitGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SFGameMode.generated.h"


class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class SEVENFLOWER_API ASFGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

	
};
