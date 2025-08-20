// Made by LSH

#pragma once

#include "Data/Spawn/SpawnInfo.h"
#include "AI/Character/Monster_Base.h"
#include "SpawnInfo_Monster.generated.h"

USTRUCT(BlueprintType)
struct FSpawnInfo_Monster : public FSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	EMonsterType MonsterName;

	UPROPERTY(EditAnywhere)
	float SpawnDuration = 0;
};