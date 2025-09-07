// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameSystem/GameInstance/HSGameInstance.h"
#include "HSSpawner_Base.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSSpawner_Base : public AActor
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AHSSpawner_Base(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma endregion

#pragma region Data

public:
	class UDataTable* GetSpawnDataTable() { return SpawnDataTable; }

	virtual struct FSpawnInfo* GetObjectData(int32 RowNum, EMapType CurrentMap = UHSGameInstance::SelectedMap) { return nullptr; }
	virtual struct FSpawnInfo* GetObjectData(FString TargetName, FString TargetPlace = TEXT("None")) { return nullptr; }

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UDataTable> SpawnDataTable;

#pragma endregion

#pragma region Setting

protected:
	void FindObjectBPClasses();
	virtual void SpawnObjects() {};

public:
	TArray<AActor*> GetSpawnedObjects() { return SpawnedObjects; }

protected:
	UPROPERTY()
	TArray<TSubclassOf<AActor>> ObjectClasses;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> SpawnedObjects;

#pragma endregion

};