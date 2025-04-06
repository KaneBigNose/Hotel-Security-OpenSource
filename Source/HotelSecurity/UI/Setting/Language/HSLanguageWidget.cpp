// Made by LSH

#include "UI/Setting/Language/HSLanguageWidget.h"
#include "Components/Button.h"
#include "Internationalization/Internationalization.h"
#include "GameInstance/HSGameInstance.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

void UHSLanguageWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	EnglishButton->OnClicked.AddDynamic(this, &ThisClass::ClickEnglishButton);
	KoreanButton->OnClicked.AddDynamic(this, &ThisClass::ClickKoreanButton);
}

#pragma endregion

#pragma region Click

void UHSLanguageWidget::ClickEnglishButton()
{
	FInternationalization::Get().SetCurrentCulture(FString("en"));
	GameInstance->SetSelectedLanguage(FName("English"));
}

void UHSLanguageWidget::ClickKoreanButton()
{
	FInternationalization::Get().SetCurrentCulture(FString("ko-KR"));
	GameInstance->SetSelectedLanguage(FName("Korean"));
}

#pragma endregion