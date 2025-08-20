// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/UI_Base.h"
#include "UI_MainMenu.generated.h"

UCLASS(Meta = (DisableNativeTick))
class HOTEL_SECURITY_API UUI_MainMenu : public UUI_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY()
	TObjectPtr<class UUI_Controller> UICon;

#pragma endregion

#pragma region Click

protected:
	UFUNCTION()
	void ClickStartButton();

	UFUNCTION()
	void ClickDictionaryButton();

	UFUNCTION()
	void ClickSettingButton();

	UFUNCTION()
	void ClickQuitButton();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> StartButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> DictionaryButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> SettingButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> QuitButton;

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_PopUp_Base> MapSelectClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_PopUp_Base> DictionaryClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_PopUp_Base> SettingClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_PopUp_Base> CreditClass;

#pragma endregion

};