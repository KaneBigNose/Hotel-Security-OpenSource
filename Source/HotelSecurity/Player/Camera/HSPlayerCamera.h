// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HSPlayerCamera.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOTEL_SECURITY_API UHSPlayerCamera : public UActorComponent
{
	GENERATED_BODY()

#pragma region Base

public:
	UHSPlayerCamera();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
	class AHSPlayer* HSPlayer;

	UPROPERTY()
	class AHSPlayerController* HSPlayerController;

#pragma endregion

#pragma region Camera

public:
	void MakeCameraShake(bool bPlayEffectSound);

protected:
	FTimerHandle NextShakeHandle;

	bool bCanCameraShake = true;

	void ResetCanShake();

protected:
	bool bIsDeadCameraRotate = false;

	void SetCameraNormalMode();

	UFUNCTION()
	void SetCameraDeathMode(class AHSMonsterBase* Attacker);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UHSPlayerCameraShake> HSPlayerCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UHSPlayerCameraShake> HangingBodyCameraShake;

#pragma endregion

};