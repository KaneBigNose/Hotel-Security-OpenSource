// Made by LSH

#include "UI/PopUp/InGame/GameOver/UI_GameOver.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameSystem/GameInstance/HSGameInstance.h"

#pragma region Base

void UUI_GameOver::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ReplayButton->OnClicked.AddDynamic(this, &ThisClass::ClickReplayButton);
	MainMenuButton->OnClicked.AddDynamic(this, &ThisClass::ClickMainMenuButton);
	QuitButton->OnClicked.AddDynamic(this, &ThisClass::ClickQuitButton);
}

#pragma endregion

#pragma region Click

void UUI_GameOver::ClickReplayButton()
{
	UHSGameInstance* GameInstance = GetWorld()->GetGameInstance<UHSGameInstance>();
	GameInstance->OpenMap(GameInstance->SelectedMap);
}

void UUI_GameOver::ClickMainMenuButton()
{
	UHSGameInstance* GameInstance = GetWorld()->GetGameInstance<UHSGameInstance>();
	GameInstance->OpenMap(EMapType::MainMenu);
}

void UUI_GameOver::ClickQuitButton()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}

#pragma endregion

#pragma region Text

void UUI_GameOver::SetDyingMessage(FText DyingMessage)
{
	DyingMessageTextBlock->SetText(DyingMessage);
}

#pragma endregion

#pragma region Input

void UUI_GameOver::InputWidget_Enter()
{
	ClickReplayButton();
}

void UUI_GameOver::InputWidget_ESC()
{
	ClickMainMenuButton();
}

#pragma endregion