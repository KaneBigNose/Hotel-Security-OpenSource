// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/HSMonsterBase/HSMonsterBase.h"
#include "AI/HSNurse/NurseInterface/HSNurseInterface.h"
#include "HSNurse.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSNurse : public AHSMonsterBase, public IHSNurseInterface
{
	GENERATED_BODY()

#pragma region Base

public:
	AHSNurse();

#pragma endregion

#pragma region Calculate

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NurseWalkSpeed = 60.f;

#pragma endregion

#pragma region Stop

protected:
	FTimerHandle StopHandle;

	float StopDuration = 1.f;

	float DefaultDelayValue = 1.f;
	float DelayedValue = 0.f;

	void ResetMovement();

public:
	void StopNurseMovement();

#pragma endregion

};