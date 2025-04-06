// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HSResolutionWidget.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSResolutionWidget : public UUserWidget
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
	void ClickHDButton();

	UFUNCTION()
	void ClickFHDButton();

	UFUNCTION()
	void ClickQHDButton();

	UFUNCTION()
	void ClickUHDButton();

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* HDButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* FHDButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QHDButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* UHDButton;

#pragma endregion

};