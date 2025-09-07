// Made by LSH

#include "UI/PopUp/InGame/GameOver/UI_GameOver.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameSystem/GameInstance/HSGameInstance.h"
#include "GameSystem/Subsystem/HSWorldSubsystem.h"

#pragma region Base

void UUI_GameOver::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ReplayButton->OnClicked.AddDynamic(this, &ThisClass::ClickReplayButton);
	MainMenuButton->OnClicked.AddDynamic(this, &ThisClass::ClickMainMenuButton);
	QuitButton->OnClicked.AddDynamic(this, &ThisClass::ClickQuitButton);
}

void UUI_GameOver::NativeConstruct()
{
	Super::NativeConstruct();

	UHSWorldSubsystem* Subsystem = GetWorld()->GetSubsystem<UHSWorldSubsystem>();

	if (Subsystem->AnomalyList.IsEmpty())
	{
		List->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	if (Subsystem->AnomalyList.Num() >= 1)
	{
		List1->SetText(FText::FromString(Subsystem->AnomalyList[0]));
	}

	if (Subsystem->AnomalyList.Num() >= 2)
	{
		List2->SetText(FText::FromString(Subsystem->AnomalyList[1]));
	}

	if (Subsystem->AnomalyList.Num() >= 3)
	{
		List3->SetText(FText::FromString(Subsystem->AnomalyList[2]));
	}

	if (Subsystem->AnomalyList.Num() >= 4)
	{
		List4->SetText(FText::FromString(Subsystem->AnomalyList[3]));
	}

	if (Subsystem->AnomalyList.Num() >= 5)
	{
		List5->SetText(FText::FromString(Subsystem->AnomalyList[4]));
	}
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