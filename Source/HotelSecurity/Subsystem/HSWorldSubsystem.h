// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Delegates/DelegateCombinations.h"
#include "HSWorldSubsystem.generated.h"

struct FAnomalyInfoBase;
struct FRespawnInfoBase;
struct FLocalizationBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnomalyEventOccur);

UCLASS()
class HOTEL_SECURITY_API UHSWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

#pragma region Base

public:
	UHSWorldSubsystem();

protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

#pragma endregion

#pragma region Data

public:
	UDataTable* GetAnomalyData() { return AnomalyData; }
	UDataTable* GetRespawnData() { return RespawnData; }

	FAnomalyInfoBase* GetAnomalyData(int32 ActorNum);
	FAnomalyInfoBase* GetAnomalyData(FName ActorName);

	FRespawnInfoBase* GetRespawnData(int32 ActorNum);

protected:
	UPROPERTY()
	UDataTable* AnomalyData;

	UPROPERTY()
	UDataTable* RespawnData;

public:
	UDataTable* GetLocalizationLocationData() { return LocalizationLocationData; }
	UDataTable* GetLocalizationAnomalyData() { return LocalizationAnomalyData; }

	FLocalizationBase* GetLocalizationLocationData(FName Original);
	FLocalizationBase* GetLocalizationAnomalyData(FName Original);

protected:
	UPROPERTY()
	UDataTable* LocalizationLocationData;

	UPROPERTY()
	UDataTable* LocalizationAnomalyData;

#pragma endregion

#pragma region Setting Anomaly

protected:
	void FindAnomalyBPClass();
	void CreateAnomalyObjects(UWorld* CurrentWorld);
	void DeleteAnomalyObjects();

public:
	TArray<class AHSAnomalyBase*> GetSpawnedAnomalys() { return SpawnedAnomalys; }

protected:
	UPROPERTY()
	TArray<TSubclassOf<class AHSAnomalyBase>> AnomalyClasses;

	UPROPERTY()
	TArray<class AHSAnomalyBase*> SpawnedAnomalys;

#pragma endregion

#pragma region Setting Monster

protected:
	virtual void FindMonsterBPClass();
	virtual void SpawnMapMonsters(UWorld* CurrentWorld);
	void DeleteHotelMonsters();

protected:
	UPROPERTY()
	TArray<class AHSMonsterBase*> SpawnedMonsters;

#pragma endregion

#pragma region Delegate

public:
	FAnomalyEventOccur AnomalyEventOccur;

#pragma endregion

#pragma region Anomaly Event

public:
	UFUNCTION()
	void EndAnomalyEvent(class AHSMonsterBase* Attacker = nullptr);
	int32 GetCurrentAnomaly() { return CurrentAnomaly; }

protected:
	FTimerHandle AnomalyEventHandle;

	void AnomalyEventTimer();

	float AnmalyEventDuration = 100.f;

protected:
	void StartRandomAnomalyEvent();
	void StartAnomalyEvent();
	void CheckAnomalyEvent();

	int32 CurrentAnomaly = 0;
	const int32 MaxAnomaly = 5;

#pragma endregion

#pragma region Anomaly Fix

public:
	void SucceedFixAnomaly();
	void FailedFixAnomaly();

	int32 GetFailCount() { return FailCount; }
	int32 GetMaxFailCount() { return MaxFailCount; }

protected:
	int32 FailCount = 0;
	int32 MaxFailCount = 3;

#pragma endregion

#pragma region Wait

protected:
	FTimerHandle WaitAnomalyEventHandle;

	float WaitAnomalyTime = 100.f;

	void WaitAnomalyTimer();

#pragma endregion

};