// Made by LSH

#include "GAS/GameplayAbility/Interact/GA_Interact.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "Character/Character/HSCharacter.h"
#include "Character/Component/Interact/HSCharacterInteract.h"
#include "Interact/HSInteractObjectBase.h"

UGA_Interact::UGA_Interact()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	HSGameplayTags::InitGameplayTags();

	AbilityTags.AddTag(HSGameplayTags::Action::Interact);

	ActivationBlockedTags.AddTag(HSGameplayTags::Cooldown::Interact);
	ActivationBlockedTags.AddTag(HSGameplayTags::State::Die);
}

bool UGA_Interact::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	AHSCharacter* Owner = Cast<AHSCharacter>(ActorInfo->AvatarActor.Get());
	UHSCharacterInteract* OwnerIntComp = Owner->GetInteractComponent();

	if (!OwnerIntComp->GetLineTraceHitObject())
	{
		return false;
	}

	return true;
}

void UGA_Interact::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	AHSCharacter* Owner = Cast<AHSCharacter>(ActorInfo->AvatarActor.Get());
	UHSCharacterInteract* OwnerIntComp = Owner->GetInteractComponent();

	OwnerIntComp->GetLineTraceHitObject()->InteractThisObject();

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}