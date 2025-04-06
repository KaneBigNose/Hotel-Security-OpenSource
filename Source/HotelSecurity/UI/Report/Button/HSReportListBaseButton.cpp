// Made by LSH

#include "UI/Report/Button/HSReportListBaseButton.h"
#include "UI/Report/HSReportBaseWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UHSReportListBaseButton::SetSelectedValueText()
{
	TArray<UUserWidget*> FoundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHSReportBaseWidget::StaticClass(), false);

	if (FoundWidgets.Num() <= 0)
	{
		return;
	}

	ReportBaseWidget = Cast<UHSReportBaseWidget>(FoundWidgets[0]);
}