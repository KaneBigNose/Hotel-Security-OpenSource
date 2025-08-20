// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/InGame/UI_PopUp_InGame.h"
#include "UI_StageClear.generated.h"

UCLASS(Meta = (DisableNativeTick))
class HOTEL_SECURITY_API UUI_StageClear : public UUI_PopUp_InGame
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Click

protected:
	UFUNCTION()
	void ClickMainMenuButton();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> MainMenuButton;

#pragma endregion

#pragma region Input

protected:
	virtual void InputWidget_Enter() override;
	virtual void InputWidget_ESC() override;

#pragma endregion

};