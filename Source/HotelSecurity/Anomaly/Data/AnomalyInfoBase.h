// Made by LSH

#pragma once

#include "AnomalyInfoBase.generated.h"

USTRUCT(BlueprintType)
struct FAnomalyInfoBase : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ActorNumber = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ActorName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString English;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Korean;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Place;

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
	int32 CLocationX = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CLocationY = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CLocationZ = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Path;
};