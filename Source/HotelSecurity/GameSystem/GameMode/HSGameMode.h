// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Delegates/DelegateCombinations.h"
#include "HSGameMode.generated.h"

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FPlayTime, int32, Hour, int32, Minute, FString, Center);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimeStop, bool, bIsStop);

#pragma endregion

UCLASS()
class HOTEL_SECURITY_API AHSGameMode : public AGameModeBase
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_Base> InGameClass;

#pragma endregion

#pragma region Timer

public:
	FPlayTime PlayTime;

	int32 GetCurrentHour();
	int32 GetCurrentMinute();

protected:
	FTimerHandle PlayTimeHandle;

	void IncreasePlayTime();

	UFUNCTION()
	void StopPlayTime(bool bIsStop);

	UFUNCTION()
	void TimeStopDuration(bool bIsStop);

protected:
	int32 InGameOneMinute = 8; // real time 4 seconds

	int32 CurrentPlayTime = 0;
	int32 EndPlayTime = 480 * InGameOneMinute;

	bool bOnCenter = true;

#pragma endregion

#pragma region Penalty

public:
	void GivePenalty();

protected:
	UFUNCTION()
	void StartTimePenalty(bool bIsStop);

public:
	FTimeStop TimeStop;

protected:
	FTimerHandle DecreaseHandle;

	float TargetDecrease = 0;

#pragma endregion

#pragma region PostProcessing

protected:
	UFUNCTION()
	void TimeStopEffect(bool bIsStop);

protected:
	FTimerHandle EffectHandle;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UMaterial> StopEffectMat;

	float CurrentRadius = 0;
	float TargetRadius = 0;
	float RadiusSpeed = 0;

#pragma endregion

};