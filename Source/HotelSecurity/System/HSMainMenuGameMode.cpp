// Made by LSH

#include "System/HSMainMenuGameMode.h"
#include "UI/MainMenu/HSMainMenu.h"
#include "GameInstance/HSGameInstance.h"
#include "Kismet/GameplayStatics.h"

void AHSMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	MainMenuWidget = Cast<UHSMainMenu>(CreateWidget(GetWorld(), MainMenuClass));
	MainMenuWidget->AddToViewport();

	if (MainMenuBGM)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), MainMenuBGM);
	}
}