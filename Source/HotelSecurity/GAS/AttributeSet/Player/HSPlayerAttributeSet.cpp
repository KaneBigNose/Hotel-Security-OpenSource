// Made by LSH

#include "GAS/AttributeSet/Player/HSPlayerAttributeSet.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "Player/Character/HSPlayer.h"
#include "Player/State/HSPlayerState.h"
#include "Components/SpotLightComponent.h"
#include "AI/Character/Monster_Base.h"

UHSPlayerAttributeSet::UHSPlayerAttributeSet()
{
	InitWalkSpeed(200);
	InitRunSpeed(450);

	InitFlashLife(800);
	InitMaxFlashLife(800);

	InitFearGage(0);
	InitMaxFearGage(100);
}

void UHSPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	AHSPlayer* Owner = Cast<AHSPlayer>(Cast<APlayerState>(GetOwningActor())->GetPawn());
	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(GetOwningAbilitySystemComponent());

	if (!Owner || !ASC)
	{
		return;
	}

	if (Data.EvaluatedData.Attribute == GetFlashLifeAttribute())
	{
		if (ASC->HasMatchingGameplayTag(HSGameplayTags::Action::Flash) && FlashLife.GetCurrentValue() > 0 && !ASC->HasMatchingGameplayTag(HSGameplayTags::State::FlashLock))
		{
			Owner->GetHandFlashLight()->bAffectsWorld = true;
		}
		else
		{
			Owner->GetHandFlashLight()->bAffectsWorld = false;
		}

		Owner->GetHandFlashLight()->MarkRenderStateDirty();
	}
	else if (Data.EvaluatedData.Attribute == GetFearGageAttribute())
	{
		if (ASC->HasMatchingGameplayTag(HSGameplayTags::State::Die))
		{
			return;
		}

		if (FearGage.GetCurrentValue() >= MaxFearGage.GetCurrentValue())
		{
			Owner->PlayerDie.Broadcast(Cast<AMonster_Base>(Data.Target.GetOwner()));
		}

		ASC->ActiveAbilitiesByTag(HSGameplayTags::State::Feared);
	}
}