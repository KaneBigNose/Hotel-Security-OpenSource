// Made by LSH

#include "UI/PopUp/MainMenu/Dictionary/UI_Dictionary.h"
#include "UI/Controller/UI_Controller.h"
#include "GameSystem/GameSave/HSSave_Dictionary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#define LOCTEXT_NAMESPACE "UI_Dictionary"

#pragma region Base

void UUI_Dictionary::NativeConstruct()
{
	UHSSave_Dictionary* Save_Dictionary = Cast<UHSSave_Dictionary>(UGameplayStatics::LoadGameFromSlot(TEXT("HSSave_Dictionary"), 0));
	bool bFindMonster = Save_Dictionary->LoadDictionaryData(MonsterName);

	if (bFindMonster)
	{
		return;
	}

	PreviewImage->SetBrushTintColor(FSlateColor(FLinearColor(0, 0, 0, 0)));

	FText ChangeText = LOCTEXT("key1", "No Data");
	Explain->SetText(ChangeText);
}

#pragma endregion

#pragma region Input

void UUI_Dictionary::InputWidget_ESC()
{
	UICon->ClosePopUpWidget(EInputModeType::UIOnly);
}

#pragma endregion

#undef LOCTEXT_NAMESPACE