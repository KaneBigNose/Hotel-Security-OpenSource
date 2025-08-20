// Made by LSH

#include "Player/State/HSPlayerState.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/AttributeSet/Player/HSPlayerAttributeSet.h"

AHSPlayerState::AHSPlayerState()
{
	PrimaryActorTick.bCanEverTick = false;

	PlayerAttributeSet = CreateDefaultSubobject<UHSPlayerAttributeSet>(TEXT("PlayerAttributeSet"));

	ASC = CreateDefaultSubobject<UHSAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	ASC->AddAttributeSetSubobject(PlayerAttributeSet.Get());
}

UAbilitySystemComponent* AHSPlayerState::GetAbilitySystemComponent() const
{
	return Cast<UAbilitySystemComponent>(ASC);
}