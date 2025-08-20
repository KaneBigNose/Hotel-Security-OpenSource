// Made by LSH

#include "GAS/GameplayEffect/Move/GE_SpeedChange.h"
#include "GAS/AttributeSet/HSAttributeSet.h"
#include "GAS/GameplayTag/HSGameplayTags.h"

UGE_SpeedChange::UGE_SpeedChange()
{
    DurationPolicy = EGameplayEffectDurationType::Instant;

    FGameplayModifierInfo SpeedModifier;
    SpeedModifier.Attribute = UHSAttributeSet::GetCurrentSpeedAttribute();
    SpeedModifier.ModifierOp = EGameplayModOp::Override;

    FSetByCallerFloat SetbyCaller;
    SetbyCaller.DataTag = HSGameplayTags::Calculation::Speed;
    SpeedModifier.ModifierMagnitude = SetbyCaller;

    Modifiers.Add(SpeedModifier);
}