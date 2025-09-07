// Made by LSH

#include "GAS/GameplayEffect/Flash/GE_ConsumeBattery.h"
#include "GAS/AttributeSet/Player/HSPlayerAttributeSet.h"
#include "GAS/GameplayTag/HSGameplayTags.h"

UGE_ConsumeBattery::UGE_ConsumeBattery()
{
    DurationPolicy = EGameplayEffectDurationType::Instant;

    FGameplayModifierInfo FlashModifier;
    FlashModifier.Attribute = UHSPlayerAttributeSet::GetFlashLifeAttribute();
    FlashModifier.ModifierOp = EGameplayModOp::Additive;

    FSetByCallerFloat SetbyCaller;
    SetbyCaller.DataTag = HSGameplayTags::Calculation::Battery;
    FlashModifier.ModifierMagnitude = SetbyCaller;

    Modifiers.Add(FlashModifier);
}