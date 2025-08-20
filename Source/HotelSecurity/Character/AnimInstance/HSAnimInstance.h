// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HSAnimInstance.generated.h"

UCLASS(Meta = (DisableNativeTick))
class HOTEL_SECURITY_API UHSAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeBeginPlay() override;

protected:
	UPROPERTY()
	TObjectPtr<class AHSCharacter> OwnerCharacter;

	UPROPERTY()
	TObjectPtr<class UHSAbilitySystemComponent> OwnerASC;

#pragma endregion

#pragma region State

protected:
	UFUNCTION()
	void TagChangeEvent_Move(struct FGameplayTag ChangeTag, int32 NewCount);

	UFUNCTION()
	void TagChangeEvent_Run(struct FGameplayTag ChangeTag, int32 NewCount);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRun;

#pragma endregion

};