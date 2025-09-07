// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Spawner/HSSpawner_Base.h"
#include "HSSpawner_Monster.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSSpawner_Monster : public AHSSpawner_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma endregion

#pragma region Data

public:
	virtual struct FSpawnInfo* GetObjectData(int32 RowNum, EMapType CurrentMap = UHSGameInstance::SelectedMap) override;
	virtual struct FSpawnInfo* GetObjectData(FString TargetName, FString TargetPlace = TEXT("None")) override;

#pragma endregion

#pragma region Setting

protected:
	virtual void SpawnObjects() override;

protected:
	UPROPERTY()
	TArray<FTimerHandle> TimerHandles;

#pragma endregion

};