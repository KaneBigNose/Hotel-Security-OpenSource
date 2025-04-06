// Made by LSH

#include "UI/Setting/Sound/HSSoundWidget.h"
#include "GameFramework/GameUserSettings.h"
#include "Components/Slider.h"
#include "Sound/SoundClass.h"

#pragma region Base

void UHSSoundWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SoundSlider->OnValueChanged.AddDynamic(this, &ThisClass::ClickSoundSlider);
}

#pragma endregion

#pragma region Click

void UHSSoundWidget::ClickSoundSlider(float SoundValue)
{
	USoundClass* MasterClass = LoadObject<USoundClass>(nullptr, TEXT("/Game/HotelSecurity/System/SC_Master"));
	if (MasterClass)
	{
		MasterClass->Properties.Volume = SoundValue;
	}
}

#pragma endregion