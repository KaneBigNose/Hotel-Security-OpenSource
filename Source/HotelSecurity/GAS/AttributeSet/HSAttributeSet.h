// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "HSAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class HOTEL_SECURITY_API UHSAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
public:
	UPROPERTY(EditAnywhere, Category = "Basic")
	FGameplayAttributeData CurrentSpeed;
	ATTRIBUTE_ACCESSORS(UHSAttributeSet, CurrentSpeed)

	UPROPERTY(EditAnywhere, Category = "Basic")
	FGameplayAttributeData WalkSpeed;
	ATTRIBUTE_ACCESSORS(UHSAttributeSet, WalkSpeed)

	UPROPERTY(EditAnywhere, Category = "Basic")
	FGameplayAttributeData RunSpeed;
	ATTRIBUTE_ACCESSORS(UHSAttributeSet, RunSpeed)
};