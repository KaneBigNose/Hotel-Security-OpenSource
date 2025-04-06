// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HSInGameBase.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSInGameBase : public UUserWidget
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

protected:
	class AHSPlayer* HSPlayer;

#pragma endregion

#pragma region Widget

public:
	class UHSAnomalyEventWidget* GetAnomalyEventWidget() { return AnomalyEventWidget; }

	void LoadingComplete();

protected:
	UPROPERTY(meta = (BindWidget))
	class UHSAimWidget* AimWidget;

	UPROPERTY(meta = (BindWidget))
	class UHSFlashWidget* FlashWidget;

	UPROPERTY(meta = (BindWidget))
	class UHSAnomalyEventWidget* AnomalyEventWidget;

	UPROPERTY(meta = (BindWidget))
	class UHSPlayTimeWidget* PlayTimeWidget;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ReportingTextBlock;

	UPROPERTY(meta = (BindWidget))
	class UHSResultWidget* ResultWidget;

	UPROPERTY(meta = (BindWidget))
	class UUserWidget* LoadingWidget;

public:
	UPROPERTY(meta = (BindWidget))
	class UHSFearWidget* FearWidget;

#pragma endregion

#pragma region Report

public:
	UFUNCTION()
	void ReportingTextTimer();

protected:
	FTimerHandle ReportingTextHandle;

	float ReportingDuration = 10.f;

	void SetReportingTextUnVisible();

#pragma endregion

#pragma region Loading

protected:
	FTimerHandle LoadingHandle;

#pragma endregion

};