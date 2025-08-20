// Made by LSH

#include "UI/PopUp/InGame/StageClear/UI_StageClear.h"
#include "Components/Button.h"
#include "GameSystem/GameInstance/HSGameInstance.h"

#pragma region Base

void UUI_StageClear::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MainMenuButton->OnClicked.AddDynamic(this, &ThisClass::ClickMainMenuButton);
}

#pragma endregion

#pragma region Click

void UUI_StageClear::ClickMainMenuButton()
{
	UHSGameInstance* GameInstance = GetWorld()->GetGameInstance<UHSGameInstance>();
	GameInstance->OpenMap(EMapType::MainMenu);
}

#pragma endregion

#pragma region Input

void UUI_StageClear::InputWidget_Enter()
{
	ClickMainMenuButton();
}

void UUI_StageClear::InputWidget_ESC()
{
	ClickMainMenuButton();
}

#pragma endregion