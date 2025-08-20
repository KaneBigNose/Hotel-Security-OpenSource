// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AT_DecreaseFear.generated.h"

UCLASS()
class HOTEL_SECURITY_API UAT_DecreaseFear : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	static UAT_DecreaseFear* CreateTask(UGameplayAbility* OwningAbility)
	{
		UAT_DecreaseFear* Task = NewAbilityTask<UAT_DecreaseFear>(OwningAbility);

		return Task;
	}

protected:
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

protected:
	void ApplyEffect(class AHSPlayer* Owner, class UHSAbilitySystemComponent* ASC);

	FTimerHandle EffectHandle;

	TSubclassOf<UGameplayEffect> ApplyEffectClass;
};