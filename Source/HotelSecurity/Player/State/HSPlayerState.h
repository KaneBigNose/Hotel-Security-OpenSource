// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "HSPlayerState.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AHSPlayerState();
	
public:
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	TObjectPtr<class UHSPlayerAttributeSet> GetPlayerAttributeSet() { return PlayerAttributeSet; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	TObjectPtr<class UHSAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	TObjectPtr<class UHSPlayerAttributeSet> PlayerAttributeSet;
};