// Made by LSH

#include "UI/PopUp/InGame/UI_PopUp_InGame.h"
#include "UI/Controller/UI_Controller.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

void UUI_PopUp_InGame::NativeConstruct()
{
	Super::NativeConstruct();

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

#pragma endregion

#pragma region Input

void UUI_PopUp_InGame::InputWidget_ESC()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->ClosePopUpWidget(EInputModeType::GameOnly);
}

#pragma endregion