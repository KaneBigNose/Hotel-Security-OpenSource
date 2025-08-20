// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Delegates/DelegateCombinations.h"
#include "AT_ConsumeBattery.generated.h"

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFlashAction, bool, bIsOn);

#pragma endregion

UCLASS()
class HOTEL_SECURITY_API UAT_ConsumeBattery : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	static UAT_ConsumeBattery* CreateTask(UGameplayAbility* OwningAbility)
	{
		UAT_ConsumeBattery* Task = NewAbilityTask<UAT_ConsumeBattery>(OwningAbility);

		return Task;
	}

public:
	static FFlashAction FlashAction;

protected:
	UPROPERTY()
	TObjectPtr<class AHSPlayer> Owner;

	UPROPERTY()
	TObjectPtr<class UHSAbilitySystemComponent> ASC;

protected:
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

protected:
	void ApplyEffect();
	void TagChangeEvent_Flash(const FGameplayTag ChangeTag, int32 NewCount);

	FTimerHandle EffectHandle;

	TSubclassOf<UGameplayEffect> ApplyEffectClass;
};