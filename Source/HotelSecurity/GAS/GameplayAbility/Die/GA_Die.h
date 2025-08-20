// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Die.generated.h"

UCLASS()
class HOTEL_SECURITY_API UGA_Die : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_Die();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
								 const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;

protected:
	void CreateGameOverWidget(FText DyingMessage);

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_PopUp_Base> GameOverClass;
};