// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/Character/Monster_Base.h"
#include "AI/Character/Nurse/NurseInterface/NurseInterface.h"
#include "Nurse.generated.h"

UCLASS()
class HOTEL_SECURITY_API ANurse : public AMonster_Base, public INurseInterface
{
	GENERATED_BODY()

#pragma region Base

public:
	ANurse(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Stop

public:
	void StopNurseMovement();

protected:
	FTimerHandle StopHandle;

	float DefaultDelayValue = 1.f;
	float DelayedValue = 0.f;

#pragma endregion

};