// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GAS/AttributeSet/Player/HSPlayerAttributeSet.h"
#include "Player/Character/HSPlayer.h"
#include "Player/State/HSPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "HSAbilitySystemComponent.generated.h"

#pragma region Declare

UENUM(BlueprintType)
enum class EBindDataType : uint8
{
	Walk		UMETA(DisplayName = "Walk"),
	Run			UMETA(DisplayName = "Run"),
	FlashLife	UMETA(DisplayName = "FlashLife"),
	FearGage	UMETA(DisplayName = "FearGage")
};

#pragma endregion

UCLASS()
class HOTEL_SECURITY_API UHSAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void ActiveAbilitiesByTag(struct FGameplayTag ActiveTag);
	void ActiveAbilitiesByTag(struct FGameplayTag ActiveTag, class AHSCharacter* Target);
	void CancelAbilitiesByTag(struct FGameplayTag CancelTag);

	FActiveGameplayEffectHandle ApplyGameplayEffect(class AHSCharacter* Target, TSubclassOf<UGameplayEffect> ApplyEffectClass);
	FActiveGameplayEffectHandle ApplyGameplayEffect(class AHSCharacter* Target, TSubclassOf<UGameplayEffect> ApplyEffectClass, FGameplayTag DataTag, float EffectValue);

	bool AddUniqueGameplayTag(struct FGameplayTag TargetTag);
	bool AddUniqueGameplayTags(struct FGameplayTagContainer TargetTags);

	template<class UserClass>
	void BindAttributeChange(EBindDataType BindDataType, UserClass* InUserObject, void (UserClass::* BindFunction)(const FOnAttributeChangeData&), OUT TObjectPtr<UHSPlayerAttributeSet>& AS)
	{
		AHSPlayer* HSPlayer = Cast<AHSPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		AHSPlayerState* PS = Cast<AHSPlayerState>(HSPlayer->GetPlayerState());
		AS = PS->GetPlayerAttributeSet();

		FGameplayAttribute TargetData;

		switch (BindDataType)
		{
		case EBindDataType::Walk:
			TargetData = AS->GetWalkSpeedAttribute();
			break;

		case EBindDataType::Run:
			TargetData = AS->GetRunSpeedAttribute();
			break;

		case EBindDataType::FlashLife:
			TargetData = AS->GetFlashLifeAttribute();
			break;

		case EBindDataType::FearGage:
			TargetData = AS->GetFearGageAttribute();
			break;
		}

		GetGameplayAttributeValueChangeDelegate(TargetData).AddUObject(InUserObject, BindFunction);
	}
};