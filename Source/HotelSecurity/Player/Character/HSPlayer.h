// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Character/Character/HSCharacter.h"
#include "Delegates/DelegateCombinations.h"
#include "HSPlayer.generated.h"

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerDie, class AMonster_Base*, Attacker);

#pragma endregion

UCLASS()
class HOTEL_SECURITY_API AHSPlayer : public AHSCharacter
{
	GENERATED_BODY()

#pragma region Base

public:
	AHSPlayer(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

#pragma endregion

#pragma region GAS

public:
	virtual class UHSAttributeSet* GetHSAttributeSet() override;

#pragma endregion

#pragma region Component

public:
	TObjectPtr<class UHSPlayerVision> GetVisionComponent() { return VisionComponent; }
	TObjectPtr<class UHSPlayerCamera> GetCameraComponent() { return CameraComponent; }

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UHSPlayerVision> VisionComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UHSPlayerCamera> CameraComponent;

#pragma endregion

#pragma region Die

public:
	FPlayerDie PlayerDie;

	UFUNCTION()
	void OnPlayerDie(class AMonster_Base* Attacker);

#pragma endregion

#pragma region Flash

public:
	class UStaticMeshComponent* GetHandFlash() { return HandFlash; }
	class USpotLightComponent* GetHandFlashLight() { return HandFlashLight; }

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> HandFlash;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USpotLightComponent> HandFlashLight;

#pragma endregion

};