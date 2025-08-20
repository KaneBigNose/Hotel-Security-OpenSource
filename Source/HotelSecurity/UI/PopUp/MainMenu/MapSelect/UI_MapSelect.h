// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/MainMenu/UI_PopUp_MainMenu.h"
#include "UI_MapSelect.generated.h"

UCLASS(Meta = (DisableNativeTick))
class HOTEL_SECURITY_API UUI_MapSelect : public UUI_PopUp_MainMenu
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

#pragma region Highlight

protected:
	virtual void InitButtons() override;

protected:
	UPROPERTY()
	TArray<TObjectPtr<class UButton>> MapButtons;

#pragma endregion

#pragma region Text

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> HotelText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> MineText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> HospitalText;

#pragma endregion

#pragma region Click

protected:
	UFUNCTION()
	void ClickHotelSelectButton();

	UFUNCTION()
	void ClickMineSelectButton();

	UFUNCTION()
	void ClickHospitalSelectButton();

	UFUNCTION()
	void ClickOldHouseSelectButton();

	UFUNCTION()
	void ClickStartButton();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> HotelButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> MineButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> HospitalButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> OldHouseButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> StartButton;

#pragma endregion

#pragma region Image

protected:
	void SettingPreviewImage(class UTexture2D* PreviewTexture);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> PreviewImage;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> PreviewNotSelect;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> PreviewHotel;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> PreviewMine;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> PreviewHospital;

#pragma endregion

#pragma region Input

protected:
	virtual void InputWidget_Enter() override;

#pragma endregion

};