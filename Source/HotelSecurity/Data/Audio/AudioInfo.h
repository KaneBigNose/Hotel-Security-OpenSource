// Made by LSH

#pragma once

#include "AudioInfo.generated.h"

USTRUCT(BlueprintType)
struct FAudioInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 Number = 0;

	UPROPERTY(EditAnywhere)
	FName Name;

	UPROPERTY(EditAnywhere)
	FName Group;

	UPROPERTY(EditAnywhere)
	FString Path;
};