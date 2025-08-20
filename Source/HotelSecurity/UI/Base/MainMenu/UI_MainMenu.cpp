// Made by LSH

#include "UI/Base/MainMenu/UI_MainMenu.h"
#include "UI/Controller/UI_Controller.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameSystem/GameMode/HSMainMenuGameMode.h"

#pragma region Base

void UUI_MainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();

	StartButton->OnClicked.AddDynamic(this, &ThisClass::ClickStartButton);
	DictionaryButton->OnClicked.AddDynamic(this, &ThisClass::ClickDictionaryButton);
	SettingButton->OnClicked.AddDynamic(this, &ThisClass::ClickSettingButton);
	QuitButton->OnClicked.AddDynamic(this, &ThisClass::ClickQuitButton);
}

#pragma endregion

#pragma region Click

void UUI_MainMenu::ClickStartButton()
{
	UICon->OpenPopUpWidget(MapSelectClass);
}

void UUI_MainMenu::ClickDictionaryButton()
{
	UICon->OpenPopUpWidget(DictionaryClass);
}

void UUI_MainMenu::ClickSettingButton()
{
	UICon->OpenPopUpWidget(SettingClass);
}

void UUI_MainMenu::ClickQuitButton()
{
	AHSMainMenuGameMode* GameMode = Cast<AHSMainMenuGameMode>(GetWorld()->GetAuthGameMode());

	UKismetSystemLibrary::QuitGame(this, Cast<APlayerController>(GameMode->PlayerControllerClass), EQuitPreference::Quit, false);
}

#pragma endregion