// Made by LSH

#include "GameSystem/GameSave/HSSave_Report.h"
#include "Kismet/GameplayStatics.h"

void UHSSave_Report::LoadReportData(int32& PlaceIdx, int32& ObjectIdx, int32& AnomalyIdx)
{
	UHSSave_Report* Save_Report = Cast<UHSSave_Report>(UGameplayStatics::LoadGameFromSlot(TEXT("HSSave_Report"), 0));

	if (!Save_Report)
	{
		return;
	}

	PlaceIdx = Save_Report->PlaceIndex;
	ObjectIdx = Save_Report->ObjectIndex;
	AnomalyIdx = Save_Report->AnomalyIndex;
}

void UHSSave_Report::SaveReportData(int32 PlaceIdx, int32 ObjectIdx, int32 AnomalyIdx)
{
	UHSSave_Report* Save_Report = Cast<UHSSave_Report>(UGameplayStatics::CreateSaveGameObject(UHSSave_Report::StaticClass()));

	Save_Report->PlaceIndex = PlaceIdx;
	Save_Report->ObjectIndex = ObjectIdx;
	Save_Report->AnomalyIndex = AnomalyIdx;

	UGameplayStatics::SaveGameToSlot(Save_Report, TEXT("HSSave_Report"), 0);
}