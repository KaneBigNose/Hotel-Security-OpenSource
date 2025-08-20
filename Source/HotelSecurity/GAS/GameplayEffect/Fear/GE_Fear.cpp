// Made by LSH

#include "GAS/GameplayEffect/Fear/GE_Fear.h"
#include "GAS/AttributeSet/Player/HSPlayerAttributeSet.h"
#include "GAS/GameplayTag/HSGameplayTags.h"

UGE_Fear::UGE_Fear()
{
    DurationPolicy = EGameplayEffectDurationType::Instant;

    FGameplayModifierInfo FearModifier;
    FearModifier.Attribute = UHSPlayerAttributeSet::GetFearGageAttribute();
    FearModifier.ModifierOp = EGameplayModOp::Additive;

    FSetByCallerFloat SetbyCaller;
    SetbyCaller.DataTag = HSGameplayTags::Calculation::Fear;
    FearModifier.ModifierMagnitude = SetbyCaller;

    Modifiers.Add(FearModifier);
}