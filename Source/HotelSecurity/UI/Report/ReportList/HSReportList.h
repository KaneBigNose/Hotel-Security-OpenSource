// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HSReportList.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSReportList : public UUserWidget
{
	GENERATED_BODY()

#pragma region Base

public:
	UHSReportList(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY()
	class UHSGameInstance* GameInstance;

	UPROPERTY()
	class UHSReportBaseWidget* ReportBaseWidget;

#pragma endregion

#pragma region Setting

protected:
	void SelectMapSubsystem();
	void SettingFNameArray();

protected:
	UPROPERTY()
	class UHSWorldSubsystem* MapSubsystem;

	UPROPERTY()
	TArray<FName> LocationNames;

	UPROPERTY()
	TArray<FName> ObjectNames;

	UPROPERTY()
	TArray<FName> AnomalyNames;

#pragma endregion

#pragma region Create Button

protected:
	void CreateAllButtons();
	void CreateLocationButtons();
	void CreateObjectButtons();
	void CreateAnomalyButtons();

protected:
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* RootBox;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* LocationScrollBox;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ObjectScrollBox;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* AnomalyScrollBox;

protected:
	void SettingListButtonStyle(class UHSReportListBaseButton* NewButton);

protected:
	UPROPERTY()
	TArray<class UHSReportListLocationButton*> LocationButtons;

	UPROPERTY()
	TArray<class UHSReportListObjectButton*> ObjectButtons;

	UPROPERTY()
	TArray<class UHSReportListAnomalyButton*> AnomalyButtons;

	class UTexture2D* ListButtonImage;
	class UTexture2D* ListButtonImageOnMouse;

#pragma endregion

};