// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HSMonsterAnimInstance.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AHSMonsterBase* HSMonster;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCharacterMovementComponent* HSMonsterMovementComponent;

#pragma endregion

#pragma region Calculate

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsMove = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSprint = false;

#pragma endregion

};