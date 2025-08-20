// Made by LSH

#include "UI/PopUp/InGame/Tutorial/UI_Tutorial.h"
#include "UI/Controller/UI_Controller.h"
#include "Components/Button.h"

#pragma region Base

void UUI_Tutorial::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();

	PreviousButton->OnClicked.AddDynamic(this, &ThisClass::Click_Previous);
	NextButton->OnClicked.AddDynamic(this, &ThisClass::Click_Next);
	WorkButton->OnClicked.AddDynamic(this, &ThisClass::InputWidget_ESC);
}

#pragma endregion

#pragma region Click

void UUI_Tutorial::Click_Previous()
{
	UICon->OpenPopUpWidget(PreviousClass);
}

void UUI_Tutorial::Click_Next()
{
	UICon->OpenPopUpWidget(NextClass);
}

#pragma endregion

#pragma region Input

void UUI_Tutorial::InputWidget_Enter()
{
	Click_Next();
}

#pragma endregion