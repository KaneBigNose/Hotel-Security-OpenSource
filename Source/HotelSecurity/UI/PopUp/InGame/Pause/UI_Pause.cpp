// Made by LSH

#include "UI/PopUp/InGame/Pause/UI_Pause.h"
#include "GameSystem/GameInstance/HSGameInstance.h"
#include "Components/Button.h"

#pragma region Base

void UUI_Pause::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ResumeButton->OnClicked.AddDynamic(this, &ThisClass::InputWidget_ESC);
	MainMenuButton->OnClicked.AddDynamic(this, &ThisClass::ClickMainMenuButton);
}

#pragma endregion

#pragma region Click

void UUI_Pause::ClickMainMenuButton()
{
	UHSGameInstance* GameInstance = GetWorld()->GetGameInstance<UHSGameInstance>();
	GameInstance->OpenMap(EMapType::MainMenu);
}

#pragma endregion

#pragma region Input

void UUI_Pause::InputWidget_Enter()
{
	InputWidget_ESC();
}

#pragma endregion