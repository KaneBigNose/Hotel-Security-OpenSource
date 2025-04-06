// Made by LSH

#include "UI/Setting/Shadow/HSShadowWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameUserSettings.h"

#pragma region Base

void UHSShadowWidget::NativeOnInitialized()
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

void UHSShadowWidget::ClickOffButton()
{
	SettingHandle->SetShadowQuality(0);
	SettingHandle->ApplySettings(false);
}

void UHSShadowWidget::ClickLowButton()
{
	SettingHandle->SetShadowQuality(1);
	SettingHandle->ApplySettings(false);
}

void UHSShadowWidget::ClickMediumButton()
{
	SettingHandle->SetShadowQuality(2);
	SettingHandle->ApplySettings(false);
}

void UHSShadowWidget::ClickHighButton()
{
	SettingHandle->SetShadowQuality(3);
	SettingHandle->ApplySettings(false);
}

#pragma endregion