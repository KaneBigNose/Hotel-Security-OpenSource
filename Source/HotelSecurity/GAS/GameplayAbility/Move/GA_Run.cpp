// Made by LSH

#include "GAS/GameplayAbility/Move/GA_Run.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/AttributeSet/HSAttributeSet.h"
#include "Character/Character/HSCharacter.h"

UGA_Run::UGA_Run()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	HSGameplayTags::InitGameplayTags();

	AbilityTags.AddTag(HSGameplayTags::State::Run);

	ActivationBlockedTags.AddTag(HSGameplayTags::State::Run);
	ActivationBlockedTags.AddTag(HSGameplayTags::State::Die);
}

void UGA_Run::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AHSCharacter* Owner = Cast<AHSCharacter>(ActorInfo->AvatarActor.Get());
	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
	UHSAttributeSet* AS = Owner->GetHSAttributeSet();

	ASC->AddUniqueGameplayTag(HSGameplayTags::State::Run);
	ASC->ApplyGameplayEffect(Owner, SpeedChangeEffectClass, HSGameplayTags::Calculation::Speed, AS->GetRunSpeed());
}

void UGA_Run::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	AHSCharacter* Owner = Cast<AHSCharacter>(ActorInfo->AvatarActor.Get());
	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
	
	if (Owner && ASC)
	{
		UHSAttributeSet* AS = Owner->GetHSAttributeSet();

		ASC->RemoveLooseGameplayTag(HSGameplayTags::State::Run);
		ASC->ApplyGameplayEffect(Owner, SpeedChangeEffectClass, HSGameplayTags::Calculation::Speed, AS->GetWalkSpeed());
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}