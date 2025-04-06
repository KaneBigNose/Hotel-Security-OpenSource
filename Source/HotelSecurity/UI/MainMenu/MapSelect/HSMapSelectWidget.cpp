// Made by LSH

#include "UI/MainMenu/MapSelect/HSMapSelectWidget.h"
#include "UI/InGame/HSInGameBase.h"
#include "UI/MainMenu/HSMainMenu.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "Player/HSPlayer/HSPlayerController.h"
#include "GameInstance/HSGameInstance.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#pragma region Base

void UHSMapSelectWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	HotelSelectButton->OnClicked.AddDynamic(this, &ThisClass::ClickHotelSelectButton);
	MineSelectButton->OnClicked.AddDynamic(this, &ThisClass::ClickMineSelectButton);
	HospitalSelectButton->OnClicked.AddDynamic(this, &ThisClass::ClickHospitalSelectButton);
	StartButton->OnClicked.AddDynamic(this, &ThisClass::ClickStartButton);

	StartButton->SetVisibility(ESlateVisibility::Hidden);
}

void UHSMapSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FString ClearText = TEXT("Clear");

	if (GameInstance->GetSelectedLanguage() == FName("Korean"))
	{
		ClearText = TEXT("클리어");
	}

	if (GameInstance->bIsClearHotel)
	{
		HotelMap->SetText(FText::FromString(ClearText));
	}
	if (GameInstance->bIsClearMine)
	{
		MineMap->SetText(FText::FromString(ClearText));
	}
	if (GameInstance->bIsClearHospital)
	{
		HospitalMap->SetText(FText::FromString(ClearText));
	}
}

#pragma endregion

#pragma region Click

void UHSMapSelectWidget::ClickHotelSelectButton()
{
	GameInstance->SetSelectedMapName(FName("Hotel"));
	SettingPreviewImage(PreviewHotel);
	StartButton->SetVisibility(ESlateVisibility::Visible);
}

void UHSMapSelectWidget::ClickMineSelectButton()
{
	GameInstance->SetSelectedMapName(FName("Mine"));
	SettingPreviewImage(PreviewMine);
	StartButton->SetVisibility(ESlateVisibility::Visible);
}

void UHSMapSelectWidget::ClickHospitalSelectButton()
{
	GameInstance->SetSelectedMapName(FName("Hospital"));
	SettingPreviewImage(PreviewHospital);
	StartButton->SetVisibility(ESlateVisibility::Visible);
}

void UHSMapSelectWidget::ClickStartButton()
{
	UGameplayStatics::OpenLevel(GetWorld(), GameInstance->GetSelectedMapName());

	GameInstance->SetCurrentOpenWidget(nullptr);
}

#pragma endregion

#pragma region Image

void UHSMapSelectWidget::SettingPreviewImage(UTexture2D* PreviewTexture)
{
	if (!PreviewTexture)
	{
		return;
	}

	FSlateBrush Brush;
	Brush.SetResourceObject(PreviewTexture);
	PreviewImage->SetBrush(Brush);
}

#pragma endregion

#pragma region Interface

void UHSMapSelectWidget::EscapeCurrentWidget()
{
	TArray<UUserWidget*> FoundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHSMainMenu::StaticClass(), false);

	Cast<UHSMainMenu>(FoundWidgets[0])->AddToViewport();

	RemoveFromParent();
}

void UHSMapSelectWidget::EnterCurrentWidget()
{
	if (GameInstance->GetSelectedMapName() == FName("None"))
	{
		return;
	}

	ClickStartButton();
}

#pragma endregion