// Made by LSH

#include "Character/AnimInstance/HSAnimInstance.h"
#include "Character/Character/HSCharacter.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/GameplayTag/HSGameplayTags.h"

#pragma region Base

void UHSAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<AHSCharacter>(GetOwningActor());
	OwnerASC = Cast<UHSAbilitySystemComponent>(OwnerCharacter->GetAbilitySystemComponent());

	if (OwnerASC)
	{
		OwnerASC->RegisterGameplayTagEvent(HSGameplayTags::State::Move, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::TagChangeEvent_Move);
		OwnerASC->RegisterGameplayTagEvent(HSGameplayTags::State::Run, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::TagChangeEvent_Run);
	}
}

#pragma endregion

#pragma region State

void UHSAnimInstance::TagChangeEvent_Move(FGameplayTag ChangeTag, int32 NewCount)
{
	bIsMove = OwnerASC->HasMatchingGameplayTag(HSGameplayTags::State::Move);
}

void UHSAnimInstance::TagChangeEvent_Run(FGameplayTag ChangeTag, int32 NewCount)
{
	bIsRun = OwnerASC->HasMatchingGameplayTag(HSGameplayTags::State::Run);
}

#pragma endregion