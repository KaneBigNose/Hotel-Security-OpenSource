// Made by LSH

#include "UI/Setting/Frame/HSFrameWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameUserSettings.h"

#pragma region Base

void UHSFrameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	F60Button->OnClicked.AddDynamic(this, &ThisClass::Click60Button);
	F120Button->OnClicked.AddDynamic(this, &ThisClass::Click120Button);
	F144Button->OnClicked.AddDynamic(this, &ThisClass::Click144Button);
	F240Button->OnClicked.AddDynamic(this, &ThisClass::Click240Button);

	SettingHandle = UGameUserSettings::GetGameUserSettings();
}

#pragma endregion

#pragma region Click

void UHSFrameWidget::Click60Button()
{
	SettingHandle->SetFrameRateLimit(60);
	SettingHandle->ApplySettings(false);
}

void UHSFrameWidget::Click120Button()
{
	SettingHandle->SetFrameRateLimit(120);
	SettingHandle->ApplySettings(false);
}

void UHSFrameWidget::Click144Button()
{
	SettingHandle->SetFrameRateLimit(144);
	SettingHandle->ApplySettings(false);
}

void UHSFrameWidget::Click240Button()
{
	SettingHandle->SetFrameRateLimit(240);
	SettingHandle->ApplySettings(false);
}

#pragma endregion