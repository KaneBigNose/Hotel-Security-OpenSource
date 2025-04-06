// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/HSMonsterBase/HSMonsterBase.h"
#include "HSBellyMan.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSBellyMan : public AHSMonsterBase
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AHSBellyMan();

#pragma endregion

#pragma region Chase

public:
	virtual void SetChaseTargetMode() override;
	virtual void SetNormalMode() override;

#pragma endregion

#pragma region Calculate

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BellyManWalkSpeed = 120.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BellyManRunSpeed = 350.f;

#pragma endregion

};