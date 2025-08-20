// Made by LSH

#include "UI/PopUp/MainMenu/Setting/UI_Setting.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "GameSystem/GameInstance/HSGameInstance.h"
#include "GameSystem/GameSave/HSSave_Setting.h"
#include "GameFramework/GameUserSettings.h"
#include "Sound/SoundClass.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

void UUI_Setting::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GameInstance = GetWorld()->GetGameInstance<UHSGameInstance>();
	SettingHandle = UGameUserSettings::GetGameUserSettings();

	Button_Apply->OnClicked.AddDynamic(this, &ThisClass::ClickButton_Apply);
	Button_Cancel->OnClicked.AddDynamic(this, &ThisClass::InputWidget_ESC);

	OffButton_Anti->OnClicked.AddDynamic(this, &ThisClass::ClickOffButton_Anti);
	LowButton_Anti->OnClicked.AddDynamic(this, &ThisClass::ClickLowButton_Anti);
	MediumButton_Anti->OnClicked.AddDynamic(this, &ThisClass::ClickMediumButton_Anti);
	HighButton_Anti->OnClicked.AddDynamic(this, &ThisClass::ClickHighButton_Anti);

	F60Button->OnClicked.AddDynamic(this, &ThisClass::Click60Button);
	F120Button->OnClicked.AddDynamic(this, &ThisClass::Click120Button);
	F144Button->OnClicked.AddDynamic(this, &ThisClass::Click144Button);
	F240Button->OnClicked.AddDynamic(this, &ThisClass::Click240Button);

	LowButton_Grapic->OnClicked.AddDynamic(this, &ThisClass::ClickLowButton_Grapic);
	MediumButton_Grapic->OnClicked.AddDynamic(this, &ThisClass::ClickMediumButton_Grapic);
	HighButton_Grapic->OnClicked.AddDynamic(this, &ThisClass::ClickHighButton_Grapic);
	UltraButton_Grapic->OnClicked.AddDynamic(this, &ThisClass::ClickUltraButton_Grapic);

	EnglishButton->OnClicked.AddDynamic(this, &ThisClass::ClickEnglishButton);
	KoreanButton->OnClicked.AddDynamic(this, &ThisClass::ClickKoreanButton);

	HDButton->OnClicked.AddDynamic(this, &ThisClass::ClickHDButton);
	FHDButton->OnClicked.AddDynamic(this, &ThisClass::ClickFHDButton);
	QHDButton->OnClicked.AddDynamic(this, &ThisClass::ClickQHDButton);
	UHDButton->OnClicked.AddDynamic(this, &ThisClass::ClickUHDButton);

	WindowedButton->OnClicked.AddDynamic(this, &ThisClass::ClickWindowedButton);
	FullScreenButton->OnClicked.AddDynamic(this, &ThisClass::ClickFullScreenButton);
	WindowedFullScreenButton->OnClicked.AddDynamic(this, &ThisClass::ClickWindowedFullScreenButton);

	OffButton_Shadow->OnClicked.AddDynamic(this, &ThisClass::ClickOffButton_Shadow);
	LowButton_Shadow->OnClicked.AddDynamic(this, &ThisClass::ClickLowButton_Shadow);
	MediumButton_Shadow->OnClicked.AddDynamic(this, &ThisClass::ClickMediumButton_Shadow);
	HighButton_Shadow->OnClicked.AddDynamic(this, &ThisClass::ClickHighButton_Shadow);

	SoundSlider->OnValueChanged.AddDynamic(this, &ThisClass::ClickSoundSlider);

	InitButtons();

	LoadSettingOption();
}

void UUI_Setting::NativeConstruct()
{
	Super::NativeConstruct();

	LoadSettingOption();
}

#pragma endregion

#pragma region Setting

void UUI_Setting::LoadSettingOption()
{
	UHSSave_Setting* Save_Setting = Cast<UHSSave_Setting>(UGameplayStatics::LoadGameFromSlot(TEXT("HSSave_Setting"), 0));
	Save_Setting->LoadSettingData(OUT Value_AntiAliasing, OUT Value_Frame, OUT Value_Grapic, OUT Value_Language, OUT Value_Resolution, OUT Value_Screen, OUT Value_Shadow, OUT Value_Sound, OUT IndexArr);

	OptionSetting();
}

void UUI_Setting::OptionSetting()
{
	SetSelectedHighlights();

	SettingHandle->SetAntiAliasingQuality(Value_AntiAliasing);
	SettingHandle->SetFrameRateLimit(Value_Frame);
	SettingHandle->SetOverallScalabilityLevel(Value_Grapic);

	FInternationalization::Get().SetCurrentCulture(Value_Language);
	if (Value_Language == TEXT("en"))
	{
		GameInstance->SelectedLanguage = ELanguageType::English;
	}
	else if (Value_Language == TEXT("ko-KR"))
	{
		GameInstance->SelectedLanguage = ELanguageType::Korean;
	}

	SettingHandle->SetScreenResolution(Value_Resolution);
	SettingHandle->SetFullscreenMode(Value_Screen);
	SettingHandle->SetShadowQuality(Value_Shadow);
	SoundMaster->Properties.Volume = Value_Sound;

	SettingHandle->ApplySettings(false);
	SettingHandle->SaveSettings();
}

void UUI_Setting::ClickButton_Apply()
{
	OptionSetting();

	UHSSave_Setting* Save_Setting = Cast<UHSSave_Setting>(UGameplayStatics::LoadGameFromSlot(TEXT("HSSave_Setting"), 0));
	Save_Setting->SaveSettingData(Value_AntiAliasing, Value_Frame, Value_Grapic, Value_Language, Value_Resolution, Value_Screen, Value_Shadow, Value_Sound, IndexArr);

	InputWidget_ESC();
}

#pragma endregion

#pragma region Highlight

void UUI_Setting::InitButtons()
{
	Buttons_Anti.Add(OffButton_Anti);
	Buttons_Anti.Add(LowButton_Anti);
	Buttons_Anti.Add(MediumButton_Anti);
	Buttons_Anti.Add(HighButton_Anti);

	Buttons_Frame.Add(F60Button);
	Buttons_Frame.Add(F120Button);
	Buttons_Frame.Add(F144Button);
	Buttons_Frame.Add(F240Button);

	Buttons_Grapic.Add(LowButton_Grapic);
	Buttons_Grapic.Add(MediumButton_Grapic);
	Buttons_Grapic.Add(HighButton_Grapic);
	Buttons_Grapic.Add(UltraButton_Grapic);

	Buttons_Language.Add(EnglishButton);
	Buttons_Language.Add(KoreanButton);

	Buttons_Resolution.Add(HDButton);
	Buttons_Resolution.Add(FHDButton);
	Buttons_Resolution.Add(QHDButton);
	Buttons_Resolution.Add(UHDButton);

	Buttons_Screen.Add(WindowedButton);
	Buttons_Screen.Add(FullScreenButton);
	Buttons_Screen.Add(WindowedFullScreenButton);

	Buttons_Shadow.Add(OffButton_Shadow);
	Buttons_Shadow.Add(LowButton_Shadow);
	Buttons_Shadow.Add(MediumButton_Shadow);
	Buttons_Shadow.Add(HighButton_Shadow);

	IndexArr.Add(3);
	IndexArr.Add(2);
	IndexArr.Add(3);
	IndexArr.Add(0);
	IndexArr.Add(1);
	IndexArr.Add(1);
	IndexArr.Add(3);
	IndexArr.Add(100);
}

void UUI_Setting::SetSelectedHighlights()
{
	Highlight(Buttons_Anti, IndexArr[0]);
	Highlight(Buttons_Frame, IndexArr[1]);
	Highlight(Buttons_Grapic, IndexArr[2]);
	Highlight(Buttons_Language, IndexArr[3]);
	Highlight(Buttons_Resolution, IndexArr[4]);
	Highlight(Buttons_Screen, IndexArr[5]);
	Highlight(Buttons_Shadow, IndexArr[6]);
	SoundSlider->Value = (float)IndexArr[7] / 100;
}

#pragma endregion

#pragma region Anti-Aliasing

void UUI_Setting::ClickOffButton_Anti() { Handle_Anti(0, 0); }
void UUI_Setting::ClickLowButton_Anti() { Handle_Anti(1, 1); }
void UUI_Setting::ClickMediumButton_Anti() { Handle_Anti(2, 2); }
void UUI_Setting::ClickHighButton_Anti() { Handle_Anti(3, 3); }

void UUI_Setting::Handle_Anti(int32 Value, int32 Index)
{
	Value_AntiAliasing = Value;
	IndexArr[0] = Index;
	Highlight(Buttons_Anti, IndexArr[0]);
}

#pragma endregion

#pragma region Frame

void UUI_Setting::Click60Button() { Handle_Frame(60, 0); }
void UUI_Setting::Click120Button() { Handle_Frame(120, 1); }
void UUI_Setting::Click144Button() { Handle_Frame(144, 2); }
void UUI_Setting::Click240Button() { Handle_Frame(240, 3); }

void UUI_Setting::Handle_Frame(float Value, int32 Index)
{
	Value_Frame = Value;
	IndexArr[1] = Index;
	Highlight(Buttons_Frame, IndexArr[1]);
}

#pragma endregion

#pragma region Grapic

void UUI_Setting::ClickLowButton_Grapic() { Handle_Grapic(0, 0); }
void UUI_Setting::ClickMediumButton_Grapic() { Handle_Grapic(1, 1); }
void UUI_Setting::ClickHighButton_Grapic() { Handle_Grapic(2, 2); }
void UUI_Setting::ClickUltraButton_Grapic() { Handle_Grapic(3, 3); }

void UUI_Setting::Handle_Grapic(int32 Value, int32 Index)
{
	Value_Grapic = Value;
	IndexArr[2] = Index;
	Highlight(Buttons_Grapic, IndexArr[2]);
}

#pragma endregion

#pragma region Language

void UUI_Setting::ClickEnglishButton() { Handle_Language(TEXT("en"), 0); }
void UUI_Setting::ClickKoreanButton() { Handle_Language(TEXT("ko-KR"), 1); }

void UUI_Setting::Handle_Language(FString Value, int32 Index)
{
	Value_Language = Value;
	IndexArr[3] = Index;
	Highlight(Buttons_Language, IndexArr[3]);
}

#pragma endregion

#pragma region Resolution

void UUI_Setting::ClickHDButton() { Handle_Resolution(FIntPoint(1280, 720), 0); }
void UUI_Setting::ClickFHDButton() { Handle_Resolution(FIntPoint(1920, 1080), 1); }
void UUI_Setting::ClickQHDButton() { Handle_Resolution(FIntPoint(2560, 1440), 2); }
void UUI_Setting::ClickUHDButton() { Handle_Resolution(FIntPoint(3840, 2160), 3); }

void UUI_Setting::Handle_Resolution(FIntPoint Value, int32 Index)
{
	Value_Resolution = Value;
	IndexArr[4] = Index;
	Highlight(Buttons_Resolution, IndexArr[4]);
}

#pragma endregion

#pragma region Screen

void UUI_Setting::ClickWindowedButton() { Handle_Screen(EWindowMode::Windowed, 0); }
void UUI_Setting::ClickFullScreenButton() { Handle_Screen(EWindowMode::Fullscreen, 1); }
void UUI_Setting::ClickWindowedFullScreenButton() { Handle_Screen(EWindowMode::WindowedFullscreen, 2); }

void UUI_Setting::Handle_Screen(EWindowMode::Type Value, int32 Index)
{
	Value_Screen = Value;
	IndexArr[5] = Index;
	Highlight(Buttons_Screen, IndexArr[5]);
}

#pragma endregion

#pragma region Shadow

void UUI_Setting::ClickOffButton_Shadow() { Handle_Shadow(0, 0); }
void UUI_Setting::ClickLowButton_Shadow() { Handle_Shadow(1, 1); }
void UUI_Setting::ClickMediumButton_Shadow() { Handle_Shadow(2, 2); }
void UUI_Setting::ClickHighButton_Shadow() { Handle_Shadow(3, 3); }

void UUI_Setting::Handle_Shadow(int32 Value, int32 Index)
{
	Value_Shadow = Value;
	IndexArr[6] = Index;
	Highlight(Buttons_Shadow, IndexArr[6]);
}

#pragma endregion

#pragma region Sound

void UUI_Setting::ClickSoundSlider(float SoundValue)
{
	IndexArr[7] = (int32)(SoundValue * 100);
	Value_Sound = SoundValue;
}

#pragma endregion

#pragma region Input

void UUI_Setting::InputWidget_Enter()
{
	ClickButton_Apply();
}

#pragma endregion