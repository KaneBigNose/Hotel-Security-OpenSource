// Made by LSH

#include "GameSystem/GameSave/HSSave_Clear.h"
#include "Kismet/GameplayStatics.h"

void UHSSave_Clear::LoadClearData(int32& ClearCount, bool& bHotel, bool& bMine, bool& bHospital)
{
	UHSSave_Clear* Save_Clear = Cast<UHSSave_Clear>(UGameplayStatics::LoadGameFromSlot(TEXT("HSSave_Clear"), 0));

	if (!Save_Clear)
	{
		return;
	}

	ClearCount = Save_Clear->MapClearCount;
	bHotel = Save_Clear->bIsClearHotel;
	bMine = Save_Clear->bIsClearMine;
	bHospital = Save_Clear->bIsClearHospital;
}

void UHSSave_Clear::SaveClearData(EMapType CurrentMap)
{
	UHSSave_Clear* Save_Clear = Cast<UHSSave_Clear>(UGameplayStatics::CreateSaveGameObject(UHSSave_Clear::StaticClass()));

	switch (CurrentMap)
	{
	case EMapType::Hotel:
		Save_Clear->bIsClearHotel = true;
		break;

	case EMapType::Mine:
		Save_Clear->bIsClearMine = true;
		break;

	case EMapType::Hospital:
		Save_Clear->bIsClearHospital = true;
		break;
	}

	UGameplayStatics::SaveGameToSlot(Save_Clear, TEXT("HSSave_Clear"), 0);
}