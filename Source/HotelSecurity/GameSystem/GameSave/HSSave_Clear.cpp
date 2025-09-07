// Made by LSH

#include "GameSystem/GameSave/HSSave_Clear.h"
#include "Kismet/GameplayStatics.h"

void UHSSave_Clear::LoadClearData(int32& ClearCount, bool& bHotel, bool& bMine, bool& bHospital, bool& bOldMotel)
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
	bOldMotel = Save_Clear->bIsClearOldMotel;
}

void UHSSave_Clear::SaveClearData(EMapType CurrentMap)
{
	UHSSave_Clear* Load_Clear = Cast<UHSSave_Clear>(UGameplayStatics::LoadGameFromSlot(TEXT("HSSave_Clear"), 0));
	UHSSave_Clear* Save_Clear = Cast<UHSSave_Clear>(UGameplayStatics::CreateSaveGameObject(UHSSave_Clear::StaticClass()));

	int32 ClearCount = 0;

	if (Load_Clear)
	{
		Save_Clear->bIsClearHotel = Load_Clear->bIsClearHotel;
		Save_Clear->bIsClearMine = Load_Clear->bIsClearMine;
		Save_Clear->bIsClearHospital = Load_Clear->bIsClearHospital;
		Save_Clear->bIsClearOldMotel = Load_Clear->bIsClearOldMotel;
	}

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

	case EMapType::OldMotel:
		Save_Clear->bIsClearOldMotel = true;
		break;
	}

	if (Save_Clear->bIsClearHotel)
	{
		ClearCount++;
	}
	if (Save_Clear->bIsClearMine)
	{
		ClearCount++;
	}
	if (Save_Clear->bIsClearHospital)
	{
		ClearCount++;
	}
	if (Save_Clear->bIsClearOldMotel)
	{
		ClearCount++;
	}

	Save_Clear->MapClearCount = ClearCount;

	UGameplayStatics::SaveGameToSlot(Save_Clear, TEXT("HSSave_Clear"), 0);
}