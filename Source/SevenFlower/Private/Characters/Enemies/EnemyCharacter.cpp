// Copyright QueueBitGames


#include "Characters/Enemies/EnemyCharacter.h"

#include "Characters/AbilitySystem/SFAbilitySystemComponent.h"
#include "Characters/AbilitySystem/SFAbilitySystemLibrary.h"
#include "Characters/AbilitySystem/SFAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "SevenFlower/SevenFlower.h"
#include "UI/Widgets/SFUserWidget.h"
#include "SFGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"


void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();
	USFAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent);
	
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<USFAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();

	if (USFUserWidget* SFUserWidget = Cast<USFUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		SFUserWidget->SetWidgetController(this);
	}
	
	if (const USFAttributeSet* AS = Cast<USFAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Health)
			{
				OnHealthChanged.Broadcast(Health.NewValue);
			}
		);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& MaxHealth)
			{
				OnMaxHealthChanged.Broadcast(MaxHealth.NewValue);
			}
		);
		
		AbilitySystemComponent->RegisterGameplayTagEvent(FSFGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&AEnemyCharacter::HitReactTagChanged
		);
		
		OnHealthChanged.Broadcast(AS->GetHealth());
		OnMaxHealthChanged.Broadcast(AS->GetMaxHealth());
	}

}

void AEnemyCharacter::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}

void AEnemyCharacter::InitializeDefaultAttributes() const
{
	USFAbilitySystemLibrary::InititalizeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

AEnemyCharacter::AEnemyCharacter()
{
	// Highlight
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<USFAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<USFAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}


void AEnemyCharacter::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}

void AEnemyCharacter::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AEnemyCharacter::GetPlayerLevel()
{
	return Level;
}
