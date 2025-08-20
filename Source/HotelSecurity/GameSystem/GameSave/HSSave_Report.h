// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HSSave_Report.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSSave_Report : public USaveGame
{
	GENERATED_BODY()
	
public:
	void LoadReportData(int32& PlaceIdx, int32& ObjectIdx, int32& AnomalyIdx);
	void SaveReportData(int32 PlaceIdx, int32 ObjectIdx, int32 AnomalyIdx);

protected:
	UPROPERTY(SaveGame)
	int32 PlaceIndex;

	UPROPERTY(SaveGame)
	int32 ObjectIndex;

	UPROPERTY(SaveGame)
	int32 AnomalyIndex;
};