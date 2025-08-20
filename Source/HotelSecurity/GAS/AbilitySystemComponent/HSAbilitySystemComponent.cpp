// Made by LSH

#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"

void UHSAbilitySystemComponent::ActiveAbilitiesByTag(FGameplayTag ActiveTag)
{
	FGameplayTagContainer ActivateTag;
	ActivateTag.AddTag(ActiveTag);

	TryActivateAbilitiesByTag(ActivateTag);
}

void UHSAbilitySystemComponent::ActiveAbilitiesByTag(FGameplayTag ActiveTag, AHSCharacter* Target)
{
	FGameplayEventData EventData;
	EventData.EventTag = ActiveTag;
	EventData.Target = Cast<AActor>(Target);

	HandleGameplayEvent(EventData.EventTag, &EventData);
}

void UHSAbilitySystemComponent::CancelAbilitiesByTag(FGameplayTag CancelTag)
{
	FGameplayTagContainer CancelTags;
	CancelTags.AddTag(CancelTag);

	CancelAbilities(&CancelTags);
}

FActiveGameplayEffectHandle UHSAbilitySystemComponent::ApplyGameplayEffect(AHSCharacter* Target, TSubclassOf<UGameplayEffect> ApplyEffectClass)
{
	FGameplayEffectContextHandle ContextHandle = MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(ApplyEffectClass, 1.0f, ContextHandle);
	UHSAbilitySystemComponent* TargetASC = Cast<UHSAbilitySystemComponent>(Target->GetAbilitySystemComponent());

	return ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, TargetASC);
}

FActiveGameplayEffectHandle UHSAbilitySystemComponent::ApplyGameplayEffect(AHSCharacter* Target, TSubclassOf<UGameplayEffect> ApplyEffectClass, FGameplayTag DataTag, float EffectValue)
{
	FGameplayEffectContextHandle ContextHandle = MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(ApplyEffectClass, 1.0f, ContextHandle);
	UHSAbilitySystemComponent* TargetASC = Cast<UHSAbilitySystemComponent>(Target->GetAbilitySystemComponent());

	SpecHandle.Data->SetSetByCallerMagnitude(DataTag, EffectValue);

	return ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, TargetASC);
}

bool UHSAbilitySystemComponent::AddUniqueGameplayTag(FGameplayTag TargetTag)
{
	if (!HasMatchingGameplayTag(TargetTag))
	{
		AddLooseGameplayTag(TargetTag);
		return true;
	}
	return false;
}

bool UHSAbilitySystemComponent::AddUniqueGameplayTags(FGameplayTagContainer TargetTags)
{
	if (!HasAnyMatchingGameplayTags(TargetTags))
	{
		AddLooseGameplayTags(TargetTags);
		return true;
	}
	return false;
}