// Made by LSH

#include "GameSystem/GameMode/HSMainMenuGameMode.h"
#include "UI/Controller/UI_Controller.h"

#pragma region Base

void AHSMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	bUseSeamlessTravel = false;

	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenBaseWidget(MainMenuClass, EInputModeType::UIOnly);
}

#pragma endregion