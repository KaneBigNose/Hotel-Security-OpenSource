// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GAS/AttributeSet/HSAttributeSet.h"
#include "HSMonsterAttributeSet.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSMonsterAttributeSet : public UHSAttributeSet
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Basic|Monster")
	FGameplayAttributeData FearDamage;
	ATTRIBUTE_ACCESSORS(UHSMonsterAttributeSet, FearDamage)
};