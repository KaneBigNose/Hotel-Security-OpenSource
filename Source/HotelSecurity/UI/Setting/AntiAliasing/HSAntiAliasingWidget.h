// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HSAntiAliasingWidget.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSAntiAliasingWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

protected:
	class UGameUserSettings* SettingHandle;

#pragma endregion

#pragma region Click

public:
	UFUNCTION()
	void ClickOffButton();

	UFUNCTION()
	void ClickLowButton();

	UFUNCTION()
	void ClickMediumButton();

	UFUNCTION()
	void ClickHighButton();

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* OffButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* LowButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MediumButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* HighButton;

#pragma endregion

};