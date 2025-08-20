// Made by LSH

#include "GAS/AttributeSet/HSAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/Character/HSPlayer.h"
#include "Player/State/HSPlayerState.h"

void UHSAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	AHSCharacter* Owner;

	if (APlayerState* PS = Cast<APlayerState>(GetOwningActor()))
	{
		Owner = Cast<AHSCharacter>(PS->GetPawn());
	}
	else
	{
		Owner = Cast<AHSCharacter>(GetOwningActor());
	}

	if (Data.EvaluatedData.Attribute == GetCurrentSpeedAttribute())
	{
		Owner->GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed.GetCurrentValue();
	}
}