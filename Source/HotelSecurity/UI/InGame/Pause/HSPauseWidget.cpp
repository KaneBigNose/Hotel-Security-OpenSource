// Made by LSH

#include "UI/InGame/Pause/HSPauseWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Player/HSPlayer/HSPlayerController.h"
#include "Player/HSPlayer/HSPlayer.h"

#pragma region Base

void UHSPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ResumeButton->OnClicked.AddDynamic(this, &ThisClass::ClickResumeButton);
	MainMenuButton->OnClicked.AddDynamic(this, &ThisClass::ClickMainMenuButton);
}

#pragma endregion

#pragma region Click

void UHSPauseWidget::ClickResumeButton()
{
	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetController());

	RemoveFromParent();

	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = false;

	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UHSPauseWidget::ClickMainMenuButton()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
}

#pragma endregion

#pragma region Interface

void UHSPauseWidget::EscapeCurrentWidget()
{
	ClickResumeButton();
}

void UHSPauseWidget::EnterCurrentWidget()
{
	ClickResumeButton();
}

#pragma endregion