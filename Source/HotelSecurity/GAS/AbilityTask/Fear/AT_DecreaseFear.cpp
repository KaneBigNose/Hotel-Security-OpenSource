// Made by LSH

#include "GAS/AbilityTask/Fear/AT_DecreaseFear.h"
#include "GAS/GameplayEffect/Fear/GE_Fear.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "GAS/AttributeSet/Player/HSPlayerAttributeSet.h"
#include "Player/Character/HSPlayer.h"
#include "Player/State/HSPlayerState.h"

void UAT_DecreaseFear::Activate()
{
	Super::Activate();

	AHSPlayer* Owner = Cast<AHSPlayer>(GetAvatarActor());
	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(Owner->GetAbilitySystemComponent());

	ApplyEffectClass = UGE_Fear::StaticClass();

	GetWorld()->GetTimerManager().SetTimer(EffectHandle, [this, Owner, ASC]()
		{
			ApplyEffect(Owner, ASC);
		}, 0.1f, true);
}

void UAT_DecreaseFear::OnDestroy(bool bInOwnerFinished)
{
	AHSPlayer* Owner = Cast<AHSPlayer>(GetAvatarActor());
	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(Owner->GetAbilitySystemComponent());

	ASC->CancelAbilitiesByTag(HSGameplayTags::State::Feared);

	Super::OnDestroy(bInOwnerFinished);
}

void UAT_DecreaseFear::ApplyEffect(AHSPlayer* Owner, UHSAbilitySystemComponent* ASC)
{
	AHSPlayerState* PS = Cast<AHSPlayerState>(Owner->GetPlayerState());
	UHSPlayerAttributeSet* PlayerAS = PS->GetPlayerAttributeSet();

	if (PlayerAS->GetFearGage() <= 0)
	{
		EndTask();
		return;
	}

	ASC->ApplyGameplayEffect(Owner, ApplyEffectClass, HSGameplayTags::Calculation::Fear, -0.02f);
}