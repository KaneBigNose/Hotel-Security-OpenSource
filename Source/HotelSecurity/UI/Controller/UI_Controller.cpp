// Made by LSH

#include "UI/Controller/UI_Controller.h"
#include "UI/PopUp/UI_PopUp_Base.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

#pragma region Widget

UUI_Base* UUI_Controller::OpenBaseWidget(TSubclassOf<UUI_Base> WidgetClass, const EInputModeType& InputModeType)
{
	if (BaseWidget)
	{
		CloseBaseWidget();
	}

	UUI_Base* Widget = CreateWidget<UUI_Base>(GetWorld(), WidgetClass);
	Widget->AddToViewport(ZOrderIndex++);
	BaseWidget = Widget;

	SetInputMode(InputModeType);

	return Widget;
}

UUI_PopUp_Base* UUI_Controller::OpenPopUpWidget(TSubclassOf<UUI_PopUp_Base> WidgetClass)
{
	if (PopUpWidget)
	{
		ClosePopUpWidget(EInputModeType::UIOnly);
	}

	UUI_PopUp_Base* Widget = CreateWidget<UUI_PopUp_Base>(GetWorld(), WidgetClass);
	PopUpWidget = Widget;
	Widget->AddToViewport(ZOrderIndex++);

	SetInputMode(EInputModeType::UIOnly);

	return Widget;
}

UUI_PopUp_Base* UUI_Controller::OpenStrongPopUpWidget(TSubclassOf<class UUI_PopUp_Base> WidgetClass)
{
	if (PopUpWidget)
	{
		ClosePopUpWidget(EInputModeType::UIOnly);
	}

	UUI_PopUp_Base* Widget = CreateWidget<UUI_PopUp_Base>(GetWorld(), WidgetClass);
	PopUpWidget = Widget;
	ZOrderIndex++;
	GEngine->GameViewport->AddViewportWidgetContent(Widget->TakeWidget(), 100);

	SetInputMode(EInputModeType::UIOnly);

	return Widget;
}

void UUI_Controller::CloseBaseWidget()
{
	if (!BaseWidget)
	{
		return;
	}

	BaseWidget->RemoveFromViewport();
	BaseWidget = nullptr;
	ZOrderIndex--;

	SetInputMode(EInputModeType::GameOnly);
}

void UUI_Controller::ClosePopUpWidget(const EInputModeType& InputModeType)
{
	if (!PopUpWidget)
	{
		return;
	}

	PopUpWidget->RemoveFromViewport();
	PopUpWidget = nullptr;
	ZOrderIndex--;

	SetInputMode(InputModeType);

	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UUI_Controller::CloseStrongPopUpWidget(const EInputModeType& InputModeType)
{
	if (!PopUpWidget)
	{
		return;
	}

	GEngine->GameViewport->RemoveViewportWidgetContent(PopUpWidget->TakeWidget());
	PopUpWidget = nullptr;
	ZOrderIndex--;

	SetInputMode(InputModeType);
}

void UUI_Controller::SetInputMode(const EInputModeType& InputModeType)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	switch (InputModeType)
	{
	case EInputModeType::GameOnly:
	{
		if (PopUpWidget)
		{
			return;
		}

		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;

		break;
	}
	case EInputModeType::UIOnly:
	{
		FInputModeUIOnly InputMode;

		if (!PopUpWidget)
		{
			InputMode.SetWidgetToFocus(BaseWidget->TakeWidget());
		}
		else
		{
			InputMode.SetWidgetToFocus(PopUpWidget->TakeWidget());
		}

		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;

		break;
	}
	case EInputModeType::GameAndUI:
	{
		FInputModeGameAndUI InputMode;

		if (!PopUpWidget)
		{
			InputMode.SetWidgetToFocus(BaseWidget->TakeWidget());
		}
		else
		{
			InputMode.SetWidgetToFocus(PopUpWidget->TakeWidget());
		}

		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;

		break;
	}
	}
}

#pragma endregion