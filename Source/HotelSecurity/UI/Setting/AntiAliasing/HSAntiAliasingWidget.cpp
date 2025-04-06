// Made by LSH

#include "UI/Setting/AntiAliasing/HSAntiAliasingWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameUserSettings.h"

#pragma region Base

void UHSAntiAliasingWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	OffButton->OnClicked.AddDynamic(this, &ThisClass::ClickOffButton);
	LowButton->OnClicked.AddDynamic(this, &ThisClass::ClickLowButton);
	MediumButton->OnClicked.AddDynamic(this, &ThisClass::ClickMediumButton);
	HighButton->OnClicked.AddDynamic(this, &ThisClass::ClickHighButton);

	SettingHandle = UGameUserSettings::GetGameUserSettings();
}

#pragma endregion

#pragma region Click

void UHSAntiAliasingWidget::ClickOffButton()
{
	SettingHandle->SetAntiAliasingQuality(0);
	SettingHandle->ApplySettings(false);
}

void UHSAntiAliasingWidget::ClickLowButton()
{
	SettingHandle->SetAntiAliasingQuality(1);
	SettingHandle->ApplySettings(false);
}

void UHSAntiAliasingWidget::ClickMediumButton()
{
	SettingHandle->SetAntiAliasingQuality(2);
	SettingHandle->ApplySettings(false);
}

void UHSAntiAliasingWidget::ClickHighButton()
{
	SettingHandle->SetAntiAliasingQuality(3);
	SettingHandle->ApplySettings(false);
}

#pragma endregion