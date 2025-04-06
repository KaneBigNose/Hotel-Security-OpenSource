// Made by LSH

#include "UI/MainMenu/HSMainMenu.h"
#include "UI/MainMenu/MapSelect/HSMapSelectWidget.h"
#include "UI/MainMenu/Description/HSDescriptionWidget_Explain.h"
#include "UI/MainMenu/Description/HSDescriptionWidget_Keyboard.h"
#include "UI/MainMenu/Credit/HSCreditWidget.h"
#include "UI/Setting/HSSettingWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "System/HSMainMenuGameMode.h"
#include "GameInstance/HSGameInstance.h"

#pragma region Base

void UHSMainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	StartButton->OnClicked.AddDynamic(this, &ThisClass::ClickStartButton);
	DescriptionButton->OnClicked.AddDynamic(this, &ThisClass::ClickDescriptionButton);
	SettingButton->OnClicked.AddDynamic(this, &ThisClass::ClickSettingButton);
	CreditButton->OnClicked.AddDynamic(this, &ThisClass::ClickCreditButton);
	QuitButton->OnClicked.AddDynamic(this, &ThisClass::ClickQuitButton);

	MapSelectWidget = Cast<UHSMapSelectWidget>(CreateWidget(GetWorld(), MapSelectClass));
	ExplainWidget = Cast<UHSDescriptionWidget_Explain>(CreateWidget(GetWorld(), ExplainClass));
	KeyboardWidget = Cast<UHSDescriptionWidget_Keyboard>(CreateWidget(GetWorld(), KeyboardClass));
	SettingWidget = Cast<UHSSettingWidget>(CreateWidget(GetWorld(), SettingClass));
	CreditWidget = Cast<UHSCreditWidget>(CreateWidget(GetWorld(), CreditClass));

	GameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

#pragma endregion

#pragma region Click

void UHSMainMenu::ClickStartButton()
{
	RemoveFromParent();
	MapSelectWidget->AddToViewport();
	GameInstance->SetCurrentOpenWidget(MapSelectWidget);
}

void UHSMainMenu::ClickDescriptionButton()
{
	RemoveFromParent();
	ExplainWidget->AddToViewport();
	GameInstance->SetCurrentOpenWidget(ExplainWidget);
}

void UHSMainMenu::ClickSettingButton()
{
	RemoveFromParent();
	SettingWidget->AddToViewport();
	GameInstance->SetCurrentOpenWidget(SettingWidget);
}

void UHSMainMenu::ClickCreditButton()
{
	RemoveFromParent();
	CreditWidget->AddToViewport();
	GameInstance->SetCurrentOpenWidget(CreditWidget);
}

void UHSMainMenu::ClickQuitButton()
{
	AHSMainMenuGameMode* GameMode = Cast<AHSMainMenuGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	UKismetSystemLibrary::QuitGame(this, Cast<APlayerController>(GameMode->PlayerControllerClass), EQuitPreference::Quit, false);
}

#pragma endregion