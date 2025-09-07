// Made by LSH

#include "GameSystem/GameSave/HSSave_Tutorial.h"
#include "Kismet/GameplayStatics.h"

bool UHSSave_Tutorial::LoadTutorialData(EMapType SelectedMap)
{
	UHSSave_Tutorial* Save_Tutorial = Cast<UHSSave_Tutorial>(UGameplayStatics::LoadGameFromSlot(TEXT("HSSave_Tutorial"), 0));

	if (!Save_Tutorial)
	{
		return true;
	}

	switch (SelectedMap)
	{
	case EMapType::Hotel:
		return Save_Tutorial->bIsHotelFirst;

	case EMapType::Mine:
		return Save_Tutorial->bIsMineFirst;

	case EMapType::Hospital:
		return Save_Tutorial->bIsHospitalFirst;
	}

	return false;
}

void UHSSave_Tutorial::SaveTutorialData(EMapType SelectedMap)
{
	UHSSave_Tutorial* Save_Tutorial = Cast<UHSSave_Tutorial>(UGameplayStatics::CreateSaveGameObject(UHSSave_Tutorial::StaticClass()));
	
	Save_Tutorial->bIsHotelFirst = LoadTutorialData(EMapType::Hotel);
	Save_Tutorial->bIsMineFirst = LoadTutorialData(EMapType::Mine);
	Save_Tutorial->bIsHospitalFirst = LoadTutorialData(EMapType::Hospital);

	switch (SelectedMap)
	{
	case EMapType::Hotel:
		Save_Tutorial->bIsHotelFirst = false;
		break;

	case EMapType::Mine:
		Save_Tutorial->bIsMineFirst = false;
		break;

	case EMapType::Hospital:
		Save_Tutorial->bIsHospitalFirst = false;
		break;
	}

	UGameplayStatics::SaveGameToSlot(Save_Tutorial, TEXT("HSSave_Tutorial"), 0);
}