// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/UI_Base.h"
#include "UI_InGame.generated.h"

UCLASS(Meta = (DisableNativeTick))
class HOTEL_SECURITY_API UUI_InGame : public UUI_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY()
	TObjectPtr<class UHSGameInstance> GameInstance;

	UPROPERTY()
	TObjectPtr<class UHSWorldSubsystem> Subsystem;

	UPROPERTY()
	TObjectPtr<class UUI_Controller> UICon;

	UPROPERTY()
	TObjectPtr<class UHSPlayerAttributeSet> PlayerAS;

#pragma endregion

#pragma region Aim

protected:
	UFUNCTION()
	void ChangeAim(bool bCanInteract);

protected:
	UPROPERTY()
	TObjectPtr<class UCanvasPanelSlot> AimCanvasSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> AimImage;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> NormalTexture;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> InteractTexture;

#pragma endregion

#pragma region Anomaly Event

protected:
	UFUNCTION()
	void OccurAnomalyEvent(int32 CurrentAnomaly, const int32 MaxAnomaly);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> AnomalyEventImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> AnomalyEventBack;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> AnomalyEventText;

#pragma endregion

#pragma region Battery

public:
	void UpdateBattery(const struct FOnAttributeChangeData& Data);

protected:
	UFUNCTION()
	void SetVisibleBattery(bool bIsVisible);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> FlashBatteryBar;

#pragma endregion

#pragma region Fear

protected:
	void UpdateFearBar(const struct FOnAttributeChangeData& Data);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> FearBar;

#pragma endregion

#pragma region Play Time

protected:
	UFUNCTION()
	void SetPlayTimeText(int32 Hour, int32 Minute, FString Center);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> PlayTimeText;

#pragma endregion

#pragma region Report

protected:
	UFUNCTION()
	void ShowReportingResult(FString SelectedLocation, FString SelectedObject, FString SelectedAnomaly);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ReportingText;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_PopUp_Base> ResultClass;

protected:
	FTimerHandle AnimationHandle;

	int32 TextIndex = 2;

	FText PrintMessage1;
	FText PrintMessage2;
	FText PrintMessage3;
	FText PrintMessage4;

#pragma endregion

};