// Made by LSH

#include "UI/Setting/Resolution/HSResolutionWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameUserSettings.h"

#pragma region Base

void UHSResolutionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HDButton->OnClicked.AddDynamic(this, &ThisClass::ClickHDButton);
	FHDButton->OnClicked.AddDynamic(this, &ThisClass::ClickFHDButton);
	QHDButton->OnClicked.AddDynamic(this, &ThisClass::ClickQHDButton);
	UHDButton->OnClicked.AddDynamic(this, &ThisClass::ClickUHDButton);

	SettingHandle = UGameUserSettings::GetGameUserSettings();
}

#pragma endregion

#pragma region Click

void UHSResolutionWidget::ClickHDButton()
{
	SettingHandle->SetScreenResolution(FIntPoint(1280, 720));
	SettingHandle->ApplySettings(false);
}

void UHSResolutionWidget::ClickFHDButton()
{
	SettingHandle->SetScreenResolution(FIntPoint(1920, 1080));
	SettingHandle->ApplySettings(false);
}

void UHSResolutionWidget::ClickQHDButton()
{
	SettingHandle->SetScreenResolution(FIntPoint(2560, 1440));
	SettingHandle->ApplySettings(false);
}

void UHSResolutionWidget::ClickUHDButton()
{
	SettingHandle->SetScreenResolution(FIntPoint(3840, 2160));
	SettingHandle->ApplySettings(false);
}

#pragma endregion