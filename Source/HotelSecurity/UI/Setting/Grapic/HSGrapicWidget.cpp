// Made by LSH

#include "UI/Setting/Grapic/HSGrapicWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameUserSettings.h"

#pragma region Base

void UHSGrapicWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	LowButton->OnClicked.AddDynamic(this, &ThisClass::ClickLowButton);
	MediumButton->OnClicked.AddDynamic(this, &ThisClass::ClickMediumButton);
	HighButton->OnClicked.AddDynamic(this, &ThisClass::ClickHighButton);
	UltraButton->OnClicked.AddDynamic(this, &ThisClass::ClickUltraButton);

	SettingHandle = UGameUserSettings::GetGameUserSettings();
}

#pragma endregion

#pragma region Click

void UHSGrapicWidget::ClickLowButton()
{
	SettingHandle->SetOverallScalabilityLevel(0);
	SettingHandle->ApplySettings(false);
}

void UHSGrapicWidget::ClickMediumButton()
{
	SettingHandle->SetOverallScalabilityLevel(1);
	SettingHandle->ApplySettings(false);
}

void UHSGrapicWidget::ClickHighButton()
{
	SettingHandle->SetOverallScalabilityLevel(2);
	SettingHandle->ApplySettings(false);
}

void UHSGrapicWidget::ClickUltraButton()
{
	SettingHandle->SetOverallScalabilityLevel(3);
	SettingHandle->ApplySettings(false);
}

#pragma endregion