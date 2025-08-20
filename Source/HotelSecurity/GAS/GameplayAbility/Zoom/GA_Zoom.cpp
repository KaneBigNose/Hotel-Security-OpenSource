// Made by LSH

#include "GAS/GameplayAbility/Zoom/GA_Zoom.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/AbilityTask/Zoom/AT_Zooming.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/Character/HSPlayer.h"
#include "Player/Component/Camera/HSPlayerCamera.h"

UGA_Zoom::UGA_Zoom()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	HSGameplayTags::InitGameplayTags();

	AbilityTags.AddTag(HSGameplayTags::Action::Zoom);

	ActivationBlockedTags.AddTag(HSGameplayTags::Action::Zoom);
	ActivationBlockedTags.AddTag(HSGameplayTags::UI::PopUp::Report);
	ActivationBlockedTags.AddTag(HSGameplayTags::UI::PopUp::Pause);
	ActivationBlockedTags.AddTag(HSGameplayTags::State::Die);
}

void UGA_Zoom::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AHSPlayer* Owner = Cast<AHSPlayer>(ActorInfo->AvatarActor.Get());
	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());

	ASC->CancelAbilitiesByTag(HSGameplayTags::Action::Flash);
	ASC->AddUniqueGameplayTag(HSGameplayTags::Action::Zoom);
	
	Task = UAT_Zooming::CreateTask(this);
	Task->ReadyForActivation();
}

void UGA_Zoom::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	AHSPlayer* Owner = Cast<AHSPlayer>(ActorInfo->AvatarActor.Get());
	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());

	Task->EndTask();

	if (Owner && ASC)
	{
		Owner->GetCameraComponent()->GetSpringArm()->TargetArmLength = 0;
		ASC->RemoveLooseGameplayTag(HSGameplayTags::Action::Zoom);
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}