// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameSystem/GameInstance/HSGameInstance.h"
#include "Delegates/DelegateCombinations.h"
#include "HSWorldSubsystem.generated.h"

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAnomalyEventOccur, int32, CurrentAnomaly, const int32, MaxAnomaly);

#pragma endregion

UCLASS()
class HOTEL_SECURITY_API UHSWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void Deinitialize() override;

public:
	void MapSetting();

protected:
	UPROPERTY()
	TObjectPtr<class AHSPlayer> HSPlayer;

	UPROPERTY()
	TObjectPtr<class UHSAbilitySystemComponent> ASC;

#pragma endregion

#pragma region Data

public:
	class UDataTable* GetAnomalyDataTable();

	class UDataTable* GetRespawnDataTable();

	struct FSpawnInfo_Anomaly* GetAnomalyData(int32 RowNum, EMapType CurrentMap = EMapType::None);
	struct FSpawnInfo_Anomaly* GetAnomalyData(FString TargetName);

	struct FSpawnInfo_Monster* GetMonsterData(int32 RowNum, EMapType CurrentMap = EMapType::None);
	struct FSpawnInfo_Monster* GetMonsterData(FString TargetName);

#pragma endregion

#pragma region Spawner

public:
	class AHSSpawner_Anomaly* GetAnomalySpawner() { return Spawner_Anomaly; }
	class AHSSpawner_Monster* GetMonsterSpawner() { return Spawner_Monster; }

protected:
	void SpawnMapSpawner();

protected:
	UPROPERTY()
	TObjectPtr<class AHSSpawner_Anomaly> Spawner_Anomaly;

protected:
	UPROPERTY()
	TObjectPtr<class AHSSpawner_Monster> Spawner_Monster;

#pragma endregion

#pragma region Anomaly Event

public:
	FAnomalyEventOccur AnomalyEventOccur;

protected:
	void AnomalyEventTimer();
	void StartAnomalyEvent();
	void CheckAnomalyCount();

protected:
	int32 CurrentAnomaly = 0;
	const int32 MaxAnomaly = 5;

	float WaitAnomalyDuration = 100;
	float DefaultAnomalyDuration = 90;

#pragma endregion

#pragma region Anomaly Fix

public:
	void SucceedFixAnomaly();
	void FailedFixAnomaly();

public:
	int32 FailCount = 0;
	const int32 MaxFailCount = 3;

#pragma endregion

};