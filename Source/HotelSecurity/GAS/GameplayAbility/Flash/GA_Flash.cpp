// Made by LSH

#include "GAS/GameplayAbility/Flash/GA_Flash.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/AbilityTask/Flash/AT_ConsumeBattery.h"
#include "Player/Character/HSPlayer.h"

UGA_Flash::UGA_Flash()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	HSGameplayTags::InitGameplayTags();

	AbilityTags.AddTag(HSGameplayTags::Action::Flash);

	ActivationBlockedTags.AddTag(HSGameplayTags::State::FlashLock);
	ActivationBlockedTags.AddTag(HSGameplayTags::UI::PopUp::Report);
	ActivationBlockedTags.AddTag(HSGameplayTags::UI::PopUp::Pause);
	ActivationBlockedTags.AddTag(HSGameplayTags::State::Die);
}

bool UGA_Flash::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
	ASC->ExecuteGameplayCue(HSGameplayTags::GameplayCue::Sound::Flash);

	if (ASC->HasMatchingGameplayTag(HSGameplayTags::Action::Flash))
	{
		ASC->CancelAbilitiesByTag(HSGameplayTags::Action::Flash);

		return false;
	}

	return true;
}

void UGA_Flash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AHSPlayer* Owner = Cast<AHSPlayer>(ActorInfo->AvatarActor.Get());
	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());

	Owner->GetHandFlash()->SetVisibility(true);
	ASC->AddUniqueGameplayTag(HSGameplayTags::Action::Flash);

	UAT_ConsumeBattery* Task = UAT_ConsumeBattery::CreateTask(this);
	Task->ReadyForActivation();
}

void UGA_Flash::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	AHSPlayer* Owner = Cast<AHSPlayer>(ActorInfo->AvatarActor.Get());
	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());

	if (Owner && ASC)
	{
		Owner->GetHandFlash()->SetVisibility(false);
		ASC->RemoveLooseGameplayTag(HSGameplayTags::Action::Flash);
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}