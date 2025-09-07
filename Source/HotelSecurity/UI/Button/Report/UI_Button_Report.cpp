// Made by LSH

#include "UI/Button/Report/UI_Button_Report.h"
#include "UI/PopUp/InGame/Report/UI_Report.h"
#include "Anomaly/HSAnomalyBase.h"
#include "GameSystem/Subsystem/HSWorldSubsystem.h"
#include "Spawner/Anomaly/HSSpawner_Anomaly.h"
#include "Data/Spawn/Anomaly/SpawnInfo_Anomaly.h"

#pragma region Base

UUI_Button_Report::UUI_Button_Report()
{
	OnClicked.AddDynamic(this, &ThisClass::SetSelectedText);
	OnClicked.AddDynamic(this, &ThisClass::CaptureObject);
}

#pragma endregion

#pragma region Click

void UUI_Button_Report::SetSelectedText()
{
	UUI_Report* ReportWidget = Cast<UUI_Report>(WidgetOwner);

	if (!ReportWidget->bCanReport)
	{
		return;
	}

	if (!PlaceValue.IsEmpty())
	{
		ReportWidget->SelectedPlace = PlaceValue;
		ReportWidget->SelectedPlaceIndex = ButtonIndex;
		ReportWidget->Highlight(ReportWidget->PlaceButtons, ButtonIndex);
	}
	if (!ObjectValue.IsEmpty())
	{
		ReportWidget->SelectedObject = ObjectValue;
		ReportWidget->SelectedObjectIndex = ButtonIndex;
		ReportWidget->Highlight(ReportWidget->ObjectButtons, ButtonIndex);
	}
	if (!AnomalyValue.IsEmpty())
	{
		ReportWidget->SelectedAnomaly = AnomalyValue;
		ReportWidget->SelectedAnomalyIndex = ButtonIndex;
		ReportWidget->Highlight(ReportWidget->AnomalyButtons, ButtonIndex);
	}
}

void UUI_Button_Report::CaptureObject()
{
	UUI_Report* ReportWidget = Cast<UUI_Report>(WidgetOwner);

	if (!ReportWidget->bCanReport)
	{
		return;
	}

	if (ObjectValue.IsEmpty())
	{
		return;
	}

	UHSWorldSubsystem* Subsystem = GetWorld()->GetSubsystem<UHSWorldSubsystem>();
	AHSSpawner_Anomaly* Spawner = Subsystem->GetAnomalySpawner();
	TArray<AActor*> SpawnedObjects = Spawner->GetSpawnedObjects();

	int32 Index = Subsystem->GetAnomalyData(ObjectIndex)->Number - 1;

	Cast<AHSAnomalyBase>(SpawnedObjects[Index])->CaptureObject();
}

#pragma endregion