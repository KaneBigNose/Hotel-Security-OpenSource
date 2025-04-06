// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/HSMonsterBase/HSMonsterBase.h"
#include "HSPlagueDoctor.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSPlagueDoctor : public AHSMonsterBase
{
	GENERATED_BODY()

#pragma region Base

public:
	AHSPlagueDoctor();

#pragma endregion

#pragma region Chase

public:
	virtual void SetChaseTargetMode() override;
	virtual void SetNormalMode() override;

#pragma endregion

#pragma region Calculate

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlagueDoctorWalkSpeed = 120.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlagueDoctorRunSpeed = 400.f;

#pragma endregion

};