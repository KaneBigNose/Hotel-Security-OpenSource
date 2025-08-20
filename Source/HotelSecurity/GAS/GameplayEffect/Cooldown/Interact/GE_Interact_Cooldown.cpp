// Made by LSH

#include "GAS/GameplayEffect/Cooldown/Interact/GE_Interact_Cooldown.h"

UGE_Interact_Cooldown::UGE_Interact_Cooldown()
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;

	FScalableFloat CooldownDuration(2);
	DurationMagnitude = FGameplayEffectModifierMagnitude(CooldownDuration);
}