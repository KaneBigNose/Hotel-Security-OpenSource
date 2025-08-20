// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/Character/Monster_Base.h"
#include "Miner.generated.h"

UCLASS()
class HOTEL_SECURITY_API AMiner : public AMonster_Base
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AMiner(const FObjectInitializer& ObjectInitializer);

public:
	class UStaticMeshComponent* GetPickAx() { return PickAx; }

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Helmet;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> HelmetFlash;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> PickAx;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USpotLightComponent> FlashLight;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UPointLightComponent> StartLight;

#pragma endregion

#pragma region Summon

public:
	void SummonHangingBody();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHangingBody> HangingBodyClass;

#pragma endregion

};