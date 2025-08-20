// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Fearing.generated.h"

UCLASS()
class HOTEL_SECURITY_API UGA_Fearing : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_Fearing();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
								 const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle,
							const FGameplayAbilityActorInfo* ActorInfo,
							const FGameplayAbilityActivationInfo ActivationInfo,
							bool bReplicateEndAbility,
							bool bWasCancelled) override;

protected:
	UFUNCTION()
	void EndMontage(class UAnimMontage* Montage, bool bInterrupted);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> FearingMontage;
};