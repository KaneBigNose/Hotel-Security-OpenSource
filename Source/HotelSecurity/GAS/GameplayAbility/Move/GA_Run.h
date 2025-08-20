// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Run.generated.h"

UCLASS()
class HOTEL_SECURITY_API UGA_Run : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_Run();

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
	UPROPERTY(EditAnywhere, Category = "GameplayEffect")
	TSubclassOf<UGameplayEffect> SpeedChangeEffectClass;
};