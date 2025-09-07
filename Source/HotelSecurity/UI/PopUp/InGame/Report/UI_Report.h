// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/InGame/UI_PopUp_InGame.h"
#include "Delegates/DelegateCombinations.h"
#include "UI_Report.generated.h"

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReportStart, FString, SelectedPlace, FString, SelectedObject, FString, SelectedAnomaly);

UENUM(BlueprintType)
enum class EButtonValueType : uint8
{
	Place		UMETA(DisplayName = "Place"),
	Object		UMETA(DisplayName = "Object"),
	Anomaly		UMETA(DisplayName = "Anomaly")
};

#pragma endregion

UCLASS(Meta = (DisableNativeTick))
class HOTEL_SECURITY_API UUI_Report : public UUI_PopUp_InGame
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

public:
	static FReportStart ReportStart;

protected:
	UPROPERTY()
	TObjectPtr<class UHSGameInstance> GameInstance;

	UPROPERTY()
	TObjectPtr<class UHSWorldSubsystem> Subsystem;

#pragma endregion

#pragma region Highlight

protected:
	void ReportingHighlight();

public:
	UPROPERTY()
	TArray<TObjectPtr<class UButton>> PlaceButtons;

	UPROPERTY()
	TArray<TObjectPtr<class UButton>> ObjectButtons;

	UPROPERTY()
	TArray<TObjectPtr<class UButton>> AnomalyButtons;

#pragma endregion

#pragma region Action Button

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> CancelButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> ReportButton;

#pragma endregion

#pragma region Report Scroll

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> PlaceScroll;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> ObjectScroll;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> AnomalyScroll;

#pragma endregion

#pragma region Report Button

protected:
	void SettingNames();
	void CreateButtons(const TArray<FString>& Names, TArray<TObjectPtr<class UButton>>& HighlightGroup, class UScrollBox* Scrollbox, EButtonValueType ValueType);
	void SettingListButtonStyle(class UUI_Button_Report* NewButton);

protected:
	TArray<FString> PlaceNames;
	TArray<FString> ObjectNames;
	TArray<FString> AnomalyNames;

#pragma endregion

#pragma region Selected

public:
	FString SelectedPlace;
	FString SelectedObject;
	FString SelectedAnomaly;

	int32 SelectedPlaceIndex;
	int32 SelectedObjectIndex;
	int32 SelectedAnomalyIndex;

#pragma endregion

#pragma region Preview

protected:
	void PreviewImageRendering();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> PreviewImage;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTextureRenderTarget2D> ObjectPreview;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UMaterial> ObjectPreview_Mat;

#pragma endregion

#pragma region Remain Chance

protected:
	void SetRemainChanceImage();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Chance1;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Chance2;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Chance3;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> RemainChance;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> DeadChance;

#pragma endregion

#pragma region Input

protected:
	virtual void InputWidget_Enter() override;

public:
	static bool bCanReport;

#pragma endregion

};