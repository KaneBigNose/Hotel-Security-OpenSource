// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HSFearWidget.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSFearWidget : public UUserWidget
{
	GENERATED_BODY()
	
#pragma region Base

public:
	UHSFearWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Widget

public:
	float GetCurrentFearPercent() { return CurrentFearValue / MaxFearValue; }

	void IncreaseFearValue();
	void IncreaseFearValue2();

protected:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* FearBar;

	float MaxFearValue = 100.f;
	float CurrentFearValue = 0.f;

	FTimerHandle FearHandle;

	void DecreaseFearValue();

#pragma endregion

};