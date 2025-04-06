// Made by LSH

#pragma once

#include "RespawnInfoBase.generated.h"

USTRUCT(BlueprintType)
struct FRespawnInfoBase : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MonsterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LocationX = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LocationY = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LocationZ = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RotationX = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RotationY = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RotationZ = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Path;
};