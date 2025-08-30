// Copyright QueueBitGames

#pragma once

#include "CoreMinimal.h"
#include "Characters/SFCharacter.h"
#include "Interaction/lightingInterface.h"
#include "UI/WidgetControllers/SFWidgetController.h"
#include "Characters/AbilitySystem/Data/CharacterClassInfo.h"
#include "EnemyCharacter.generated.h"

class UEnemiesWidgetController;
class USFWidgetController;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class SEVENFLOWER_API AEnemyCharacter : public ASFCharacter, public IlightingInterface
{
	GENERATED_BODY()
public:
	AEnemyCharacter();
	
	/** Enemy Interface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** end Enemy Interface */

	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** end Combat Interface */
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};
