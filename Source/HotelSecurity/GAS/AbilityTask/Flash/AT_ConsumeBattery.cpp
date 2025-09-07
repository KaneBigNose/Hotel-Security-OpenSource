// Made by LSH

#include "GAS/AbilityTask/Flash/AT_ConsumeBattery.h"
#include "GAS/GameplayEffect/Flash/GE_ConsumeBattery.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "Player/Character/HSPlayer.h"

FFlashAction UAT_ConsumeBattery::FlashAction;

void UAT_ConsumeBattery::Activate()
{
	Super::Activate();

	Owner = Cast<AHSPlayer>(GetAvatarActor());
	ASC = Cast<UHSAbilitySystemComponent>(Owner->GetAbilitySystemComponent());
	ASC->RegisterGameplayTagEvent(HSGameplayTags::Action::Flash, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::TagChangeEvent_Flash);

	ApplyEffectClass = UGE_ConsumeBattery::StaticClass();

	ApplyEffect();

	FlashAction.Broadcast(true);

	GetWorld()->GetTimerManager().SetTimer(EffectHandle, this, &ThisClass::ApplyEffect, 0.1f, true);
}

void UAT_ConsumeBattery::OnDestroy(bool bInOwnerFinished)
{
	GetWorld()->GetTimerManager().ClearTimer(EffectHandle);

	ApplyEffect();

	FlashAction.Broadcast(false);

	Super::OnDestroy(bInOwnerFinished);
}

void UAT_ConsumeBattery::ApplyEffect()
{
	ASC->ApplyGameplayEffect(Owner, ApplyEffectClass, HSGameplayTags::Calculation::Battery, -0.1f);
}

void UAT_ConsumeBattery::TagChangeEvent_Flash(const FGameplayTag ChangeTag, int32 NewCount)
{
	if (!ASC->HasMatchingGameplayTag(HSGameplayTags::Action::Flash))
	{
		EndTask();
	}
}