// Made by LSH

#pragma once

#include "Anomaly/Data/AnomalyInfoBase.h"
#include "LocalizationBase.generated.h"

USTRUCT(BlueprintType)
struct FLocalizationBase : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Original;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString English;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Korean;
};