// Made by LSH

#include "GAS/GameplayAbility/Fear/GA_Fearing.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Character/HSPlayer.h"
#include "Player/Component/Camera/HSPlayerCamera.h"

UGA_Fearing::UGA_Fearing()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	HSGameplayTags::InitGameplayTags();

	AbilityTags.AddTag(HSGameplayTags::Action::Fearing);
}

void UGA_Fearing::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AHSCharacter* Owner = Cast<AHSCharacter>(ActorInfo->AvatarActor.Get());
	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
	AHSPlayer* Target = Cast<AHSPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UHSAbilitySystemComponent* TargetASC = Cast<UHSAbilitySystemComponent>(Target->GetAbilitySystemComponent());
	UAnimInstance* Anim = Owner->GetMesh()->GetAnimInstance();

	Anim->OnMontageEnded.RemoveDynamic(this, &ThisClass::EndMontage);
	Anim->OnMontageEnded.AddDynamic(this, &ThisClass::EndMontage);

	ASC->AddUniqueGameplayTag(HSGameplayTags::Action::Fearing);
	ASC->PlayMontage(this, ActivationInfo, FearingMontage, 1);
	
	Target->MakeNoise(2.f, Target, Target->GetActorLocation());

	TargetASC->ExecuteGameplayCue(HSGameplayTags::GameplayCue::Camera::Shake_HangingBody);
	TargetASC->ExecuteGameplayCue(HSGameplayTags::GameplayCue::Sound::Fearing);
}

void UGA_Fearing::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	AHSCharacter* Owner = Cast<AHSCharacter>(ActorInfo->AvatarActor.Get());

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	Owner->Destroy();
}

void UGA_Fearing::EndMontage(UAnimMontage* Montage, bool bInterrupted)
{
	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
	ASC->CancelAbilitiesByTag(HSGameplayTags::Action::Fearing);
}