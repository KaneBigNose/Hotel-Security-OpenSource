// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Delegates/DelegateCombinations.h"
#include "UI/Interface/HSUIInterface.h"
#include "HSReportBaseWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReportCancelEvent);

UCLASS()
class HOTEL_SECURITY_API UHSReportBaseWidget : public UUserWidget, public IHSUIInterface
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Widget

public:
	class UTextBlock* GetSelectedValueTextBlock() { return SelectedValueTextBlock; }

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* ReportBaseImage;

	UPROPERTY(meta = (BindWidget))
	class UHSReportList* ReportList;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ReportButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SelectedValueTextBlock;

#pragma endregion

#pragma region Report

public:
	UFUNCTION()
	void CancelReport();

	UFUNCTION()
	void StartAnomalyReport();

public:
	FReportCancelEvent ReportCancelEvent;

public:
	FName SelectedLocation;
	FName SelectedObject;
	FName SelectedAnomaly;

#pragma endregion

#pragma region Interface

public:
	virtual void EscapeCurrentWidget() override;
	virtual void EnterCurrentWidget() override;

#pragma endregion

};