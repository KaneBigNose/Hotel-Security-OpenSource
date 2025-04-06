// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HSGameOver.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSGameOver : public UUserWidget
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundWave* GameOverSound;

#pragma endregion

#pragma region Click

public:
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
	class UTextBlock* DyingMessageTextBlock;

	UPROPERTY(meta = (BindWidget))
	class UButton* ReplayButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

#pragma endregion

};