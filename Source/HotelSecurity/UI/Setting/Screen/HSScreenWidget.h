// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HSScreenWidget.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSScreenWidget : public UUserWidget
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
	void ClickWindowedButton();

	UFUNCTION()
	void ClickFullScreenButton();

	UFUNCTION()
	void ClickWindowedFullScreenButton();

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* WindowedButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* FullScreenButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* WindowedFullScreenButton;

#pragma endregion

};