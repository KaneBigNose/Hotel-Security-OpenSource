// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HSMainMenu.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSMainMenu : public UUserWidget
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

protected:
	class UHSGameInstance* GameInstance;

#pragma endregion

#pragma region Click

public:
	UFUNCTION()
	void ClickStartButton();

	UFUNCTION()
	void ClickDescriptionButton();

	UFUNCTION()
	void ClickSettingButton();

	UFUNCTION()
	void ClickCreditButton();

	UFUNCTION()
	void ClickQuitButton();

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* DescriptionButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* SettingButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CreditButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UHSMapSelectWidget> MapSelectClass;

	UPROPERTY()
	class UHSMapSelectWidget* MapSelectWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UHSDescriptionWidget_Explain> ExplainClass;

	UPROPERTY()
	class UHSDescriptionWidget_Explain* ExplainWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UHSDescriptionWidget_Keyboard> KeyboardClass;

	UPROPERTY()
	class UHSDescriptionWidget_Keyboard* KeyboardWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UHSSettingWidget> SettingClass;

	UPROPERTY()
	class UHSSettingWidget* SettingWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UHSCreditWidget> CreditClass;

	UPROPERTY()
	class UHSCreditWidget* CreditWidget;

#pragma endregion

};