// Made by LSH

#include "GAS/GameplayEffect/Flash/GE_ConsumeBattery.h"
#include "GAS/AttributeSet/Player/HSPlayerAttributeSet.h"

UGE_ConsumeBattery::UGE_ConsumeBattery()
{
    DurationPolicy = EGameplayEffectDurationType::Instant;

    FGameplayModifierInfo FlashModifier;
    FlashModifier.Attribute = UHSPlayerAttributeSet::GetFlashLifeAttribute();
    FlashModifier.ModifierOp = EGameplayModOp::Additive;
    FlashModifier.ModifierMagnitude = FScalableFloat(-0.1f);

    Modifiers.Add(FlashModifier);
}