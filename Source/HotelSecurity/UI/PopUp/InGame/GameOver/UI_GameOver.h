// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/InGame/UI_PopUp_InGame.h"
#include "UI_GameOver.generated.h"

UCLASS(Meta = (DisableNativeTick))
class HOTEL_SECURITY_API UUI_GameOver : public UUI_PopUp_InGame
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

#pragma endregion

#pragma region Click

protected:
	UFUNCTION()
	void ClickReplayButton();

	UFUNCTION()
	void ClickMainMenuButton();

	UFUNCTION()
	void ClickQuitButton();

#pragma endregion

#pragma region Widget

public:
	void SetDyingMessage(FText DyingMessage);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> DyingMessageTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> ReplayButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> QuitButton;

#pragma endregion

#pragma region Anomaly

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> List;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> List1;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> List2;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> List3;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> List4;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> List5;

#pragma endregion

#pragma region Input

protected:
	virtual void InputWidget_Enter() override;

	virtual void InputWidget_ESC() override;

#pragma endregion

};