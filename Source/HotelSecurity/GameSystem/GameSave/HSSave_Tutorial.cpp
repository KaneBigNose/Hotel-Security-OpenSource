// Made by LSH

#include "GameSystem/GameSave/HSSave_Tutorial.h"
#include "Kismet/GameplayStatics.h"

void UHSSave_Tutorial::LoadTutorialData(bool& bFirst)
{
	UHSSave_Tutorial* Save_Tutorial = Cast<UHSSave_Tutorial>(UGameplayStatics::LoadGameFromSlot(TEXT("HSSave_Tutorial"), 0));

	if (!Save_Tutorial)
	{
		bFirst = true;
		return;
	}

	bFirst = Save_Tutorial->bIsFirstPlay;
}

void UHSSave_Tutorial::SaveTutorialData(bool bFirst)
{
	UHSSave_Tutorial* Save_Tutorial = Cast<UHSSave_Tutorial>(UGameplayStatics::CreateSaveGameObject(UHSSave_Tutorial::StaticClass()));
	Save_Tutorial->bIsFirstPlay = bFirst;

	UGameplayStatics::SaveGameToSlot(Save_Tutorial, TEXT("HSSave_Tutorial"), 0);
}