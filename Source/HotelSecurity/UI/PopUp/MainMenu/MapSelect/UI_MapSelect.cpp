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
	OldMotelButton->OnClicked.AddDynamic(this, &ThisClass::ClickOldMotelSelectButton);
	StartButton->OnClicked.AddDynamic(this, &ThisClass::ClickStartButton);

	StartButton->SetVisibility(ESlateVisibility::Hidden);

	InitButtons();
}

void UUI_MapSelect::NativeConstruct()
{
	Super::NativeConstruct();

	bool bIsClearHotel = false, bIsClearMine = false, bIsClearHospital = false, bIsClearOldMotel = false;

	UHSSave_Clear* Save_Clear = Cast<UHSSave_Clear>(UGameplayStatics::LoadGameFromSlot(TEXT("HSSave_Clear"), 0));
	if (Save_Clear)
	{
		Save_Clear->LoadClearData(OUT MapClearCount, OUT bIsClearHotel, OUT bIsClearMine, OUT bIsClearHospital, OUT bIsClearOldMotel);
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
	if (bIsClearOldMotel)
	{
		OldMotelText->SetText(ClearText);
	}

	if (MapClearCount >= 2)
	{
		Lock1->SetVisibility(ESlateVisibility::Hidden);
		Lock2->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (MapClearCount == 1)
	{
		Lock1->SetVisibility(ESlateVisibility::Visible);
		Lock2->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		Lock1->SetVisibility(ESlateVisibility::Visible);
		Lock2->SetVisibility(ESlateVisibility::Visible);
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
	MapButtons.Add(OldMotelButton);
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

void UUI_MapSelect::ClickOldMotelSelectButton()
{
	if (MapClearCount < OpenOldMotelCount)
	{
		SettingPreviewImage(PreviewNotSelect);
		Highlight(MapButtons, 100);
		StartButton->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	GameInstance->SelectedMap = EMapType::OldMotel;
	SettingPreviewImage(PreviewOldMotel);
	StartButton->SetVisibility(ESlateVisibility::Visible);
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