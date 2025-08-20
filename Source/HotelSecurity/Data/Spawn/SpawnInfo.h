// Made by LSH

#pragma once

#include "SpawnInfo.generated.h"

USTRUCT(BlueprintType)
struct FSpawnInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 Number = 0;

	UPROPERTY(EditAnywhere)
	FString Map_En;

	UPROPERTY(EditAnywhere)
	FString Map_Ko;

	UPROPERTY(EditAnywhere)
	int32 LocationX = 0;

	UPROPERTY(EditAnywhere)
	int32 LocationY = 0;

	UPROPERTY(EditAnywhere)
	int32 LocationZ = 0;

	UPROPERTY(EditAnywhere)
	FString Path;
};