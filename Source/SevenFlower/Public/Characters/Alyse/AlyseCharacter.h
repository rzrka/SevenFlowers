// Copyright QueueBitGames

#pragma once

#include "CoreMinimal.h"
#include "Characters/SFCharacter.h"
#include "AlyseCharacter.generated.h"


class UGameplayAbility;
/**
 * 
 */
UCLASS()
class SEVENFLOWER_API AAlyseCharacter : public ASFCharacter
{
	GENERATED_BODY()

public:
	AAlyseCharacter();
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;


	/** Combat Inerface */
	virtual int32 GetPlayerLevel() override; 
	/** end Combat Inerface */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isCrouching = false;
	
	const float WalkSpeed = 300.f;
	const float RunSpeed = 600.f;

	
protected:
	void InitCharacterAbilities();

	
private:
	virtual void InitAbilityActorInfo() override;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCameraComponent> ViewCamera;

	// TODO переделать в hashmap
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
