// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "HSCharacter.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

#pragma region Base

public:
	AHSCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma endregion

#pragma region GAS

public:
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual class UHSAttributeSet* GetHSAttributeSet() PURE_VIRTUAL(AHSCharacter::GetHSAttributeSet, return nullptr;);

protected:
	void GiveAbilities();

protected:
	UPROPERTY(EditAnywhere, Category = "HSCharacter|GAS")
	TArray<TSubclassOf<class UGameplayAbility>> CharacterAbilities;

	UPROPERTY(EditAnywhere, Category = "HSCharacter|GAS")
	TObjectPtr<class UHSAbilitySystemComponent> ASC;

#pragma endregion

#pragma region Interact

public:
	class UHSCharacterInteract* GetInteractComponent() { return InteractComp; }

protected:
	UPROPERTY()
	TObjectPtr<class UHSCharacterInteract> InteractComp;

#pragma endregion

};