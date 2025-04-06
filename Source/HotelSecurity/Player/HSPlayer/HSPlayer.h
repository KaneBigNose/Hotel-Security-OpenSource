// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "Delegates/DelegateCombinations.h"
#include "HSPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerDieDelegate, class AHSMonsterBase*, Attacker);

UCLASS()
class HOTEL_SECURITY_API AHSPlayer : public ACharacter
{
	GENERATED_BODY()

#pragma region Base

public:
	AHSPlayer();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	FGameplayTagContainer& GetHSPlayerStateContainer() { return HSPlayerStateContainer; }
	class UCameraComponent* GetCameraComponent() { return Camera; }
	class UCameraComponent* GetDeathViewCameraComponent() { return DeathViewCamera; }
	class USpringArmComponent* GetSpringArmComponent() { return SpringArm; }
	class USphereComponent* GetHeartBeatRangeComponent() { return HeartBeatRange; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AHSPlayerController* HSPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* DeathViewCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* HandFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpotLightComponent* HandFlashLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|HeartBeat")
	class USphereComponent* HeartBeatRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|HeartBeat")
	float HeartBeatRangeRadius = 1200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer HSPlayerStateContainer;

protected:
	UPROPERTY()
	class UHSGameInstance* GameInstance;

	UPROPERTY()
	class UHSWorldSubsystem* MapSubsystem;

#pragma endregion

#pragma region Calculate

public:
	FVector AttackerLocation;

	float PlayerWalkSpeed = 200.f;
	float PlayerRunSpeed = 450.f;
	float PlayerCrouchedSpeed = 100.f;

	float CameraArmLength = 0.f;
	float ZoomCameraArmLength = -300.f;
	float CameraSpeed = 24.f;

#pragma endregion

#pragma region Component

public:
	class UHSPlayerSound* GetHSPlayerSoundComponent() { return HSPlayerSoundComponent; }
	class UHSPlayerVision* GetHSPlayerVisionComponent() { return HSPlayerVisionComponent; }
	class UHSPlayerCamera* GetHSPlayerCameraComponent() { return HSPlayerCameraComponent; }
	class UHSPlayerInteract* GetHSPlayerInteractComponent() { return HSPlayerInteractComponent; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHSPlayerSound* HSPlayerSoundComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHSPlayerVision* HSPlayerVisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHSPlayerCamera* HSPlayerCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHSPlayerInteract* HSPlayerInteractComponent;

#pragma endregion

#pragma region Die

public:
	UFUNCTION()
	void OnPlayerDie(class AHSMonsterBase* Attacker);

	void CreateDieWidget(FText DyingMessage);

	UFUNCTION()
	void ChangeDieSound(class AHSMonsterBase* Attacker);

protected:
	FTimerHandle DieHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UHSGameOver> GameOverClass;

#pragma endregion

#pragma region Flash

public:
	void SetFlashOnOffMode(bool bTurnOnFlash);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FlashLife = 800;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxFlashLife = 800;

	FTimerHandle FlashLifeSpanHandle;

	void FlashLifeTimer(bool bStop);
	void FlashLifeSpan();

#pragma endregion

#pragma region Delegate

public:
	FPlayerDieDelegate PlayerDieDelegate;

#pragma endregion

};