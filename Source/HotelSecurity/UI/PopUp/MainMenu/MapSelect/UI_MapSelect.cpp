// Made by LSH

#include "UI/PopUp/MainMenu/MapSelect/UI_MapSelect.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameSystem/GameInstance/HSGameInstance.h"
#include "GameSystem/GameSave/HSSave_Clear.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "UI_MapSelect"

#pragma region Base

void UUI_MapSelect::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GameInstance = GetWorld()->GetGameInstance<UHSGameInstance>();

	HotelButton->OnClicked.AddDynamic(this, &ThisClass::ClickHotelSelectButton);
	MineButton->OnClicked.AddDynamic(this, &ThisClass::ClickMineSelectButton);
	HospitalButton->OnClicked.AddDynamic(this, &ThisClass::ClickHospitalSelectButton);
	OldHouseButton->OnClicked.AddDynamic(this, &ThisClass::ClickOldHouseSelectButton);
	StartButton->OnClicked.AddDynamic(this, &ThisClass::ClickStartButton);

	StartButton->SetVisibility(ESlateVisibility::Hidden);

	InitButtons();
}

void UUI_MapSelect::NativeConstruct()
{
	Super::NativeConstruct();

	int32 MapClearCount = 0;
	bool bIsClearHotel = false, bIsClearMine = false, bIsClearHospital = false;

	UHSSave_Clear* Save_Clear = Cast<UHSSave_Clear>(UGameplayStatics::LoadGameFromSlot(TEXT("HSGameSaveSlot"), 0));
	if (Save_Clear)
	{
		Save_Clear->LoadClearData(OUT MapClearCount, OUT bIsClearHotel, OUT bIsClearMine, OUT bIsClearHospital);
	}

	FText ClearText = LOCTEXT("key1", "Clear");

	if (bIsClearHotel)
	{
		HotelText->SetText(ClearText);
	}
	if (bIsClearMine)
	{
		MineText->SetText(ClearText);
	}
	if (bIsClearHospital)
	{
		HospitalText->SetText(ClearText);
	}

	SettingPreviewImage(PreviewNotSelect);
}

#pragma endregion

#pragma region Highlight

void UUI_MapSelect::InitButtons()
{
	MapButtons.Add(HotelButton);
	MapButtons.Add(MineButton);
	MapButtons.Add(HospitalButton);
	MapButtons.Add(OldHouseButton);
}

#pragma endregion

#pragma region Click

void UUI_MapSelect::ClickHotelSelectButton()
{
	GameInstance->SelectedMap = EMapType::Hotel;
	SettingPreviewImage(PreviewHotel);
	StartButton->SetVisibility(ESlateVisibility::Visible);
	Highlight(MapButtons, 0);
}

void UUI_MapSelect::ClickMineSelectButton()
{
	GameInstance->SelectedMap = EMapType::Mine;
	SettingPreviewImage(PreviewMine);
	StartButton->SetVisibility(ESlateVisibility::Visible);
	Highlight(MapButtons, 1);
}

void UUI_MapSelect::ClickHospitalSelectButton()
{
	GameInstance->SelectedMap = EMapType::Hospital;
	SettingPreviewImage(PreviewHospital);
	StartButton->SetVisibility(ESlateVisibility::Visible);
	Highlight(MapButtons, 2);
}

void UUI_MapSelect::ClickOldHouseSelectButton()
{
	StartButton->SetVisibility(ESlateVisibility::Hidden);
	Highlight(MapButtons, 3);
}

void UUI_MapSelect::ClickStartButton()
{
	GameInstance->OpenMap(GameInstance->SelectedMap);
}

#pragma endregion

#pragma region Image

void UUI_MapSelect::SettingPreviewImage(UTexture2D* PreviewTexture)
{
	FSlateBrush Brush;
	Brush.SetResourceObject(PreviewTexture);
	PreviewImage->SetBrush(Brush);
}

#pragma endregion

#pragma region Input

void UUI_MapSelect::InputWidget_Enter()
{
	if (GameInstance->SelectedMap == EMapType::None)
	{
		return;
	}

	ClickStartButton();
}

#pragma endregion

#undef LOCTEXT_NAMESPACE