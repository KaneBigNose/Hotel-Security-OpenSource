// Made by LSH

#include "GAS/GameplayAbility/Die/GA_Die.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GameSystem/GameInstance/HSGameInstance.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/PopUp/InGame/GameOver/UI_GameOver.h"
#include "Player/Character/HSPlayer.h"

#define LOCTEXT_NAMESPACE "GA_Die"

UGA_Die::UGA_Die()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	HSGameplayTags::InitGameplayTags();

	AbilityTags.AddTag(HSGameplayTags::State::Die);

	ActivationBlockedTags.AddTag(HSGameplayTags::State::Die);
}

void UGA_Die::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AHSPlayer* Owner = Cast<AHSPlayer>(ActorInfo->AvatarActor.Get());
	UHSGameInstance* GameInstance = GetWorld()->GetGameInstance<UHSGameInstance>();
	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
	FText DyingMessage = LOCTEXT("key1", "You Died");

	ASC->AddUniqueGameplayTag(HSGameplayTags::State::Die);
	ASC->ExecuteGameplayCue(HSGameplayTags::GameplayCue::Sound::Die);

	if (ASC->HasMatchingGameplayTag(HSGameplayTags::State::Feared))
	{
		DyingMessage = LOCTEXT("key2", "You fainted in Fear");
		
	}
	else if(ASC->HasMatchingGameplayTag(HSGameplayTags::State::Fired))
	{
		DyingMessage = LOCTEXT("key3", "You are Fired");
	}

	FTimerHandle DieHandle;
	GetWorld()->GetTimerManager().SetTimer(DieHandle, [this, DyingMessage, ASC]()
		{
			CreateGameOverWidget(DyingMessage);
			ASC->CancelAbilitiesByTag(HSGameplayTags::State::Die);
		}, 2.f, false);
}

void UGA_Die::CreateGameOverWidget(FText DyingMessage)
{
	AHSPlayer* Owner = Cast<AHSPlayer>(GetAvatarActorFromActorInfo());
	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
	UHSGameInstance* GameInstance = GetWorld()->GetGameInstance<UHSGameInstance>();
	UUI_Controller* UICon = GameInstance->GetSubsystem<UUI_Controller>();
	UUI_GameOver* GameOverWidget = Cast<UUI_GameOver>(UICon->OpenPopUpWidget(GameOverClass));
	
	GameOverWidget->SetDyingMessage(DyingMessage);

	ASC->AddUniqueGameplayTag(HSGameplayTags::UI::PopUp::GameOver);
}

#undef LOCTEXT_NAMESPACE