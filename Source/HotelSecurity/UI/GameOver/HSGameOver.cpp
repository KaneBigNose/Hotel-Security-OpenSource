// Made by LSH

#include "UI/GameOver/HSGameOver.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/HSGameInstance.h"
#include "System/HSGameMode.h"

#pragma region Base

void UHSGameOver::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ReplayButton->OnClicked.AddDynamic(this, &ThisClass::ClickReplayButton);
	MainMenuButton->OnClicked.AddDynamic(this, &ThisClass::ClickMainMenuButton);
	QuitButton->OnClicked.AddDynamic(this, &ThisClass::ClickQuitButton);

	if (GameOverSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), GameOverSound);
	}
}

#pragma endregion

#pragma region Click

void UHSGameOver::ClickReplayButton()
{
	UHSGameInstance* GameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	UGameplayStatics::OpenLevel(GetWorld(), GameInstance->GetSelectedMapName());
}

void UHSGameOver::ClickMainMenuButton()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
}

void UHSGameOver::ClickQuitButton()
{
	AHSGameMode* GameMode = Cast<AHSGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	UKismetSystemLibrary::QuitGame(this, Cast<APlayerController>(GameMode->PlayerControllerClass), EQuitPreference::Quit, false);
}

#pragma endregion

#pragma region Message

void UHSGameOver::SetDyingMessage(FText DyingMessage)
{
	DyingMessageTextBlock->SetText(DyingMessage);
}

#pragma endregion