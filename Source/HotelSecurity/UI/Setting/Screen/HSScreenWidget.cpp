// Made by LSH

#include "UI/Setting/Screen/HSScreenWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameUserSettings.h"

#pragma region Base

void UHSScreenWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	WindowedButton->OnClicked.AddDynamic(this, &ThisClass::ClickWindowedButton);
	FullScreenButton->OnClicked.AddDynamic(this, &ThisClass::ClickFullScreenButton);
	WindowedFullScreenButton->OnClicked.AddDynamic(this, &ThisClass::ClickWindowedFullScreenButton);

	SettingHandle = UGameUserSettings::GetGameUserSettings();
}

#pragma endregion

#pragma region Click

void UHSScreenWidget::ClickWindowedButton()
{
	SettingHandle->SetFullscreenMode(EWindowMode::Windowed);
	SettingHandle->ApplySettings(false);
}

void UHSScreenWidget::ClickFullScreenButton()
{
	SettingHandle->SetFullscreenMode(EWindowMode::Fullscreen);
	SettingHandle->ApplySettings(false);
}

void UHSScreenWidget::ClickWindowedFullScreenButton()
{
	SettingHandle->SetFullscreenMode(EWindowMode::WindowedFullscreen);
	SettingHandle->ApplySettings(false);
}

#pragma endregion