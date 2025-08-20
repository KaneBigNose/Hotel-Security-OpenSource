// Made by LSH

#include "UI/PopUp/MainMenu/UI_PopUp_MainMenu.h"
#include "UI/Controller/UI_Controller.h"

#pragma region Input

void UUI_PopUp_MainMenu::InputWidget_ESC()
{
	UUI_Controller* Controller = GetGameInstance()->GetSubsystem<UUI_Controller>();
	Controller->ClosePopUpWidget(EInputModeType::UIOnly);
}

#pragma endregion