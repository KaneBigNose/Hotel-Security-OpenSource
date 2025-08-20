// Made by LSH

#pragma once

#include "Data/Spawn/SpawnInfo.h"
#include "SpawnInfo_Anomaly.generated.h"

USTRUCT(BlueprintType)
struct FSpawnInfo_Anomaly : public FSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Object_En;

	UPROPERTY(EditAnywhere)
	FString Object_Ko;

	UPROPERTY(EditAnywhere)
	FString Place_En;

	UPROPERTY(EditAnywhere)
	FString Place_Ko;

	UPROPERTY(EditAnywhere)
	int32 RotationX = 0;

	UPROPERTY(EditAnywhere)
	int32 RotationY = 0;

	UPROPERTY(EditAnywhere)
	int32 RotationZ = 0;

	UPROPERTY(EditAnywhere)
	int32 CLocationX = 0;

	UPROPERTY(EditAnywhere)
	int32 CLocationY = 0;

	UPROPERTY(EditAnywhere)
	int32 CLocationZ = 0;
};