// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/HSMonsterBase/HSMonsterBase.h"
#include "HSMiner.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSMiner : public AHSMonsterBase
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AHSMiner();

public:
	class UStaticMeshComponent* GetPickAx() { return PickAx; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Helmet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* HelmetFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* PickAx;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpotLightComponent* FlashLight;

#pragma endregion

#pragma region Chase

public:
	virtual void SetChaseTargetMode() override;
	virtual void SetNormalMode() override;

#pragma endregion

#pragma region Calculate

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinerWalkSpeed = 180.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinerRunSpeed = 350.f;

#pragma endregion

#pragma region Summon

public:
	void SummonHangingBody();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AHSHangingBody> HangingBodyClass;

#pragma endregion

};