// Copyright QueueBitGames


#include "SFGameplayTags.h"
#include "GameplayTagsManager.h"

FSFGameplayTags FSFGameplayTags::GameplayTags;

void FSFGameplayTags::InitializeNativeGameplayTags()
{
	// Primary Attributes
    GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Primary.Strength"), 
        FString("Increases physical damage")
    );
    	 
    GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Primary.Intelligence"), 
        FString("Increases magical damage")
    );
        	 
    GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Primary.Resilience"), 
        FString("Increases Armor and Armor Penetration")
     );
        	 
    GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Primary.Vigor"), 
        FString("Increases Health")
    );

	
    // Secondary Attributes
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.Armor"), 
	    FString("Reduces damage taken, improves Block Chance")
	);
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.ArmorPenetration"), 
	    FString("Ignores Percentage of enemy Armor, Increases Critical Hit Chance")
	);
	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.BlockChance"), 
	    FString("Chance to cut incoming damage in half")
	);
	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.CriticalHitChance"), 
	   FString("Chance to double damage plus critical hit bonus")
	);
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.CriticalHitDamage"), 
	   FString("Bonus damage added when a critical hit is scored")
	);
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.CriticalHitResistance"), 
	   FString("Reduces Critical Hit Chance of attacking enemies")
	);
	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.HealthRegeneration"), 
	   FString("Amount of Health regenerated every 1 second")
	);
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.ManaRegeneration"), 
	   FString("Amount of Mana regenerated every 1 second")
	);
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.MaxHealth"), 
	   FString("Maximum amount of Health obtainable")
	);
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.MaxMana"), 
	   FString("Maximum amount of Mana obtainable")
	);

	// Input Tags
	
	GameplayTags.InputTag_WeakAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.WeakAttack"), 
		FString("Input Tag for Weak Attack")
	);

	GameplayTags.InputTag_StrongAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.StrongAttack"), 
		FString("Input Tag for Strong Attack")
	);

	GameplayTags.InputTag_Dodge = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.Dodge"), 
		FString("Input Tag for Dodge")
	);

	GameplayTags.InputTag_1Spell = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.1Spell"), 
		FString("Input Tag for 2Spell")
	);

	GameplayTags.InputTag_2Spell = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.2Spell"), 
		FString("Input Tag for 2Spell")
	);

	GameplayTags.InputTag_3Spell = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.3Spell"), 
		FString("Input Tag for 3Spell")
	);

	GameplayTags.InputTag_4Spell = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.4Spell"), 
		FString("Input Tag for 4Spell")
	);

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage"), 
		FString("Damage")
	);
}
