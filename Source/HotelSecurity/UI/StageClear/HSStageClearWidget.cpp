// Made by LSH

#include "UI/StageClear/HSStageClearWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/HSGameInstance.h"

#pragma region Base

void UHSStageClearWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MainMenuButton->OnClicked.AddDynamic(this, &ThisClass::ClickMainMenuButton);

	if (StageClearSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), StageClearSound);
	}
}

#pragma endregion

#pragma region Click

void UHSStageClearWidget::ClickMainMenuButton()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
}

#pragma endregion

#pragma region Interface

void UHSStageClearWidget::EscapeCurrentWidget()
{
	ClickMainMenuButton();
}

void UHSStageClearWidget::EnterCurrentWidget()
{
	ClickMainMenuButton();

	UHSGameInstance* GameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->SetCurrentOpenWidget(nullptr);
}

#pragma endregion