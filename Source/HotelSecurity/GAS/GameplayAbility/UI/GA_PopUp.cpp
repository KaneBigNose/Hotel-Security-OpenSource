// Made by LSH

#include "GAS/GameplayAbility/UI/GA_PopUp.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "GameSystem/GameInstance/HSGameInstance.h"
#include "UI/Controller/UI_Controller.h"

UGA_PopUp::UGA_PopUp()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	HSGameplayTags::InitGameplayTags();

	ActivationBlockedTags.AddTag(HSGameplayTags::State::Die);
}

void UGA_PopUp::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UHSGameInstance* GameInstance = GetWorld()->GetGameInstance<UHSGameInstance>();
	UUI_Controller* UICon = GameInstance->GetSubsystem<UUI_Controller>();

	UICon->OpenPopUpWidget(PopUpClass);

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}