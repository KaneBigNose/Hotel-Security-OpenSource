// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HSLanguageWidget.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSLanguageWidget : public UUserWidget
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
	void ClickEnglishButton();

	UFUNCTION()
	void ClickKoreanButton();

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* EnglishButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* KoreanButton;

#pragma endregion

};