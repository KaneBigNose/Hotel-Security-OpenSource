// Made by LSH

#include "System/HSGameMode.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "Player/HSPlayer/HSPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/InGame/HSInGameBase.h"
#include "UI/Report/HSReportBaseWidget.h"
#include "UI/MainMenu/HSMainMenu.h"
#include "GameInstance/HSGameInstance.h"

#pragma region Base

AHSGameMode::AHSGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBP(TEXT("/Game/HotelSecurity/Player/Blueprint/BP_HSPlayer.BP_HSPlayer_C"));
	if (PlayerPawnBP.Succeeded())
	{
		DefaultPawnClass = PlayerPawnBP.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBP(TEXT("/Game/HotelSecurity/Player/Blueprint/BP_HSPlayerController.BP_HSPlayerController_C"));
	if (PlayerControllerBP.Succeeded())
	{
		PlayerControllerClass = PlayerControllerBP.Class;
	}
}

void AHSGameMode::BeginPlay()
{
	Super::BeginPlay();

	MainMenuWidget = Cast<UHSMainMenu>(CreateWidget(GetWorld(), MainMenuClass));

	InGameBaseWidget = Cast<UHSInGameBase>(CreateWidget(GetWorld(), InGameBaseClass));

	SettingInGame();

	AHSPlayerController* HSPlayerController = Cast<AHSPlayerController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetController());

	FInputModeGameOnly InputMode;
	HSPlayerController->SetInputMode(InputMode);
	HSPlayerController->bShowMouseCursor = false;

	GetWorld()->GetTimerManager().SetTimer(LoadingHandle, this, &ThisClass::StartGameplay, 3.f, false);

	GameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->StageClearDelegate.AddDynamic(this, &ThisClass::PlayTimeStopTimer);
}

#pragma endregion

#pragma region Loading

void AHSGameMode::StartGameplay()
{
	InGameBaseWidget->LoadingComplete();

	PlayTimeTimer();
}

#pragma endregion

#pragma region Widget

void AHSGameMode::SettingMainMenu()
{
	MainMenuWidget->AddToViewport();
	InGameBaseWidget->RemoveFromParent();
}

void AHSGameMode::SettingInGame()
{
	InGameBaseWidget->AddToViewport();
	MainMenuWidget->RemoveFromParent();
}

#pragma endregion

#pragma region Timer

int32 AHSGameMode::GetCurrentHour()
{
	int32 CurrentHour = CurrentPlayTime / 60 + 22;

	if (CurrentHour >= 24)
	{
		CurrentHour -= 24;
	}

	return CurrentHour;
}

int32 AHSGameMode::GetCurrentMinute()
{
	int32 CurrentMinute = CurrentPlayTime % 60;

	return CurrentMinute;
}

void AHSGameMode::PlayTimeTimer()
{
	GetWorld()->GetTimerManager().SetTimer(PlayTimeHandle, this, &ThisClass::IncreasePlayTime, InGameOneMinute, true);
}

void AHSGameMode::PlayTimeStopTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(PlayTimeHandle);
}

void AHSGameMode::IncreasePlayTime()
{
	if (CurrentPlayTime >= EndPlayTime)
	{
		GameInstance->StageClearDelegate.Broadcast();
	}
	else
	{
		CurrentPlayTime++;
	}
}

#pragma endregion