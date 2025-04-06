// Made by LSH

#include "UI/MainMenu/Credit/HSCreditWidget.h"
#include "UI/MainMenu/HSMainMenu.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#pragma region Interface

void UHSCreditWidget::EscapeCurrentWidget()
{
	TArray<UUserWidget*> FoundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHSMainMenu::StaticClass(), false);

	Cast<UHSMainMenu>(FoundWidgets[0])->AddToViewport();

	RemoveFromParent();
}

void UHSCreditWidget::EnterCurrentWidget()
{
	EscapeCurrentWidget();
}

#pragma endregion