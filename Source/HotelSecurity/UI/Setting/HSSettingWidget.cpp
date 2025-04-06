// Made by LSH

#include "UI/Setting/HSSettingWidget.h"
#include "UI/MainMenu/HSMainMenu.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#pragma region Interface

void UHSSettingWidget::EscapeCurrentWidget()
{
	TArray<UUserWidget*> FoundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHSMainMenu::StaticClass(), false);

	Cast<UHSMainMenu>(FoundWidgets[0])->AddToViewport();

	RemoveFromParent();
}

void UHSSettingWidget::EnterCurrentWidget()
{
	EscapeCurrentWidget();
}

#pragma endregion