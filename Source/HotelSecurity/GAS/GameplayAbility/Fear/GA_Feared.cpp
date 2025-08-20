// Made by LSH

#include "GAS/GameplayAbility/Fear/GA_Feared.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/AbilityTask/Fear/AT_DecreaseFear.h"

UGA_Feared::UGA_Feared()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	HSGameplayTags::InitGameplayTags();

	AbilityTags.AddTag(HSGameplayTags::State::Feared);

	ActivationBlockedTags.AddTag(HSGameplayTags::State::Feared);
	ActivationBlockedTags.AddTag(HSGameplayTags::State::Die);
}

void UGA_Feared::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());

	ASC->AddUniqueGameplayTag(HSGameplayTags::State::Feared);

	UAT_DecreaseFear* Task = UAT_DecreaseFear::CreateTask(this);
	Task->ReadyForActivation();
}

void UGA_Feared::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());

	if (ASC)
	{
		ASC->RemoveLooseGameplayTag(HSGameplayTags::State::Feared);
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}