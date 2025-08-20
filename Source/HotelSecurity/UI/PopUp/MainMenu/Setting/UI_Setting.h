// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/MainMenu/UI_PopUp_MainMenu.h"
#include "UI_Setting.generated.h"

UCLASS(Meta = (DisableNativeTick))
class HOTEL_SECURITY_API UUI_Setting : public UUI_PopUp_MainMenu
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<class UHSGameInstance> GameInstance;

#pragma endregion

#pragma region Setting

protected:
	void LoadSettingOption();
	void OptionSetting();

	UFUNCTION()
	void ClickButton_Apply();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Apply;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Cancel;

	UPROPERTY()
	TObjectPtr<class UGameUserSettings> SettingHandle;

protected:
	int32 Value_AntiAliasing = 3;
	float Value_Frame = 144;
	int32 Value_Grapic = 3;
	FString Value_Language = TEXT("en");
	FIntPoint Value_Resolution = FIntPoint(1920, 1080);
	EWindowMode::Type Value_Screen = EWindowMode::Fullscreen;
	int32 Value_Shadow = 3;
	float Value_Sound = 1;

#pragma endregion

#pragma region Highlight

protected:
	virtual void InitButtons() override;
	void SetSelectedHighlights();

protected:
	UPROPERTY()
	TArray<int32> IndexArr;

	UPROPERTY()
	TArray<TObjectPtr<class UButton>> Buttons_Anti;

	UPROPERTY()
	TArray<TObjectPtr<class UButton>> Buttons_Frame;

	UPROPERTY()
	TArray<TObjectPtr<class UButton>> Buttons_Grapic;

	UPROPERTY()
	TArray<TObjectPtr<class UButton>> Buttons_Language;

	UPROPERTY()
	TArray<TObjectPtr<class UButton>> Buttons_Resolution;

	UPROPERTY()
	TArray<TObjectPtr<class UButton>> Buttons_Screen;

	UPROPERTY()
	TArray<TObjectPtr<class UButton>> Buttons_Shadow;

#pragma endregion

#pragma region Anti-Aliasing

protected:
	UFUNCTION()
	void ClickOffButton_Anti();

	UFUNCTION()
	void ClickLowButton_Anti();

	UFUNCTION()
	void ClickMediumButton_Anti();

	UFUNCTION()
	void ClickHighButton_Anti();

	void Handle_Anti(int32 Value, int32 Index);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> OffButton_Anti;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> LowButton_Anti;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> MediumButton_Anti;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> HighButton_Anti;

#pragma endregion

#pragma region Frame

protected:
	UFUNCTION()
	void Click60Button();

	UFUNCTION()
	void Click120Button();

	UFUNCTION()
	void Click144Button();

	UFUNCTION()
	void Click240Button();

	void Handle_Frame(float Value, int32 Index);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> F60Button;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> F120Button;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> F144Button;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> F240Button;

#pragma endregion

#pragma region Grapic

protected:
	UFUNCTION()
	void ClickLowButton_Grapic();

	UFUNCTION()
	void ClickMediumButton_Grapic();

	UFUNCTION()
	void ClickHighButton_Grapic();

	UFUNCTION()
	void ClickUltraButton_Grapic();

	void Handle_Grapic(int32 Value, int32 Index);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> LowButton_Grapic;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> MediumButton_Grapic;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> HighButton_Grapic;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> UltraButton_Grapic;

#pragma endregion

#pragma region Language

protected:
	UFUNCTION()
	void ClickEnglishButton();

	UFUNCTION()
	void ClickKoreanButton();

	void Handle_Language(FString Value, int32 Index);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> EnglishButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> KoreanButton;

#pragma endregion

#pragma region Resolution

protected:
	UFUNCTION()
	void ClickHDButton();

	UFUNCTION()
	void ClickFHDButton();

	UFUNCTION()
	void ClickQHDButton();

	UFUNCTION()
	void ClickUHDButton();

	void Handle_Resolution(FIntPoint Value, int32 Index);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> HDButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> FHDButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> QHDButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> UHDButton;

#pragma endregion

#pragma region Screen

protected:
	UFUNCTION()
	void ClickWindowedButton();

	UFUNCTION()
	void ClickFullScreenButton();

	UFUNCTION()
	void ClickWindowedFullScreenButton();

	void Handle_Screen(EWindowMode::Type Value, int32 Index);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> WindowedButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> FullScreenButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> WindowedFullScreenButton;

#pragma endregion

#pragma region Shadow

protected:
	UFUNCTION()
	void ClickOffButton_Shadow();

	UFUNCTION()
	void ClickLowButton_Shadow();

	UFUNCTION()
	void ClickMediumButton_Shadow();

	UFUNCTION()
	void ClickHighButton_Shadow();

	void Handle_Shadow(int32 Value, int32 Index);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> OffButton_Shadow;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> LowButton_Shadow;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> MediumButton_Shadow;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> HighButton_Shadow;

#pragma endregion

#pragma region Sound

protected:
	UFUNCTION()
	void ClickSoundSlider(float SoundValue);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundClass> SoundMaster;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USlider> SoundSlider;

#pragma endregion

#pragma region Input

protected:
	virtual void InputWidget_Enter() override;

#pragma endregion

};