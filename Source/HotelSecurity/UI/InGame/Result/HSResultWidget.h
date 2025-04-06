// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HSResultWidget.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSResultWidget : public UUserWidget
{
	GENERATED_BODY()
	
#pragma region Base

public:
	UHSResultWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* ResultBaseImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ResultText;

#pragma endregion

#pragma region Report

public:
	void ShowReportResultImage(bool bSuccessed);

protected:
	FTimerHandle RemoveImageHandle;

	float RemoveImageDuration = 2.f;

	void RemoveReportImage();

#pragma endregion

};