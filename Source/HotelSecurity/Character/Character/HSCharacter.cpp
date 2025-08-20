// Made by LSH

#include "Character/Character/HSCharacter.h"
#include "Character/Component/Interact/HSCharacterInteract.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"

#pragma region Base

AHSCharacter::AHSCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	InteractComp = CreateDefaultSubobject<UHSCharacterInteract>(TEXT("InteractComponent"));
}

void AHSCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (FGameplayAbilitySpec& Spec : ASC->GetActivatableAbilities())
	{
		if (Spec.IsActive())
		{
			ASC->ClearAbility(Spec.Handle);
		}
	}

	Super::EndPlay(EndPlayReason);
}

#pragma endregion

#pragma region GAS

UAbilitySystemComponent* AHSCharacter::GetAbilitySystemComponent() const
{
	return Cast<UAbilitySystemComponent>(ASC);
}

void AHSCharacter::GiveAbilities()
{
	if (!ASC)
	{
		return;
	}

	for (auto CharacterAbilitie : CharacterAbilities)
	{
		FGameplayAbilitySpec AbilitySpec(CharacterAbilitie, 1, INDEX_NONE);

		ASC->GiveAbility(AbilitySpec);
	}
}

#pragma endregion