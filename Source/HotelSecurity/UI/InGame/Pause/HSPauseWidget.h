// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Interface/HSUIInterface.h"
#include "HSPauseWidget.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSPauseWidget : public UUserWidget, public IHSUIInterface
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Click

public:
	UFUNCTION()
	void ClickResumeButton();

	UFUNCTION()
	void ClickMainMenuButton();

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton;

#pragma endregion

#pragma region Interface

public:
	virtual void EscapeCurrentWidget() override;
	virtual void EnterCurrentWidget() override;

#pragma endregion

};