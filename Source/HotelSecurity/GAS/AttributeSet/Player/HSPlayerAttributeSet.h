// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GAS/AttributeSet/HSAttributeSet.h"
#include "HSPlayerAttributeSet.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSPlayerAttributeSet : public UHSAttributeSet
{
	GENERATED_BODY()

public:
	UHSPlayerAttributeSet();

protected:
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
public:
	UPROPERTY(EditAnywhere, Category = "Basic|Player")
	FGameplayAttributeData FlashLife;
	ATTRIBUTE_ACCESSORS(UHSPlayerAttributeSet, FlashLife)

	UPROPERTY(EditAnywhere, Category = "Basic|Player")
	FGameplayAttributeData MaxFlashLife;
	ATTRIBUTE_ACCESSORS(UHSPlayerAttributeSet, MaxFlashLife)

	UPROPERTY(EditAnywhere, Category = "Basic|Player")
	FGameplayAttributeData FearGage;
	ATTRIBUTE_ACCESSORS(UHSPlayerAttributeSet, FearGage)

	UPROPERTY(EditAnywhere, Category = "Basic|Player")
	FGameplayAttributeData MaxFearGage;
	ATTRIBUTE_ACCESSORS(UHSPlayerAttributeSet, MaxFearGage)
};