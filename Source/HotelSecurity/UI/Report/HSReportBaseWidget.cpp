// Made by LSH

#include "UI/Report/HSReportBaseWidget.h"
#include "UI/Report/ReportList/HSReportList.h"
#include "UI/InGame/HSInGameBase.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameInstance/HSGameInstance.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

void UHSReportBaseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UCanvasPanelSlot* ReportBaseCanvasSlot = Cast<UCanvasPanelSlot>(ReportBaseImage->Slot);
	ReportBaseCanvasSlot->SetPosition(FVector2D(-750, -400));
	ReportBaseCanvasSlot->SetSize(FVector2D(1500, 800));

	UCanvasPanelSlot* ReportListCanvasSlot = Cast<UCanvasPanelSlot>(ReportList->Slot);
	ReportListCanvasSlot->SetPosition(FVector2D(-650, -270));
	ReportListCanvasSlot->SetSize(FVector2D(1300, 500));

	CancelButton->OnClicked.AddDynamic(this, &ThisClass::CancelReport);
	ReportButton->OnClicked.AddDynamic(this, &ThisClass::StartAnomalyReport);

	FString MapName = FPaths::GetCleanFilename(GetWorld()->GetMapName());


	if (MapName.EndsWith(TEXT("Hotel")))
	{
		SelectedLocation = FName("Hotel_Private");
		SelectedObject = FName("Ashtrays");
		SelectedAnomaly = FName("Location");
	}
	else if (MapName.EndsWith(TEXT("Mine")))
	{
		SelectedLocation = FName("Zone_Red");
		SelectedObject = FName("Brick");
		SelectedAnomaly = FName("Location");
	}
	else if (MapName.EndsWith(TEXT("Hospital")))
	{
		SelectedLocation = FName("Floor_1");
		SelectedObject = FName("Medicine");
		SelectedAnomaly = FName("Location");
	}
}

#pragma endregion

#pragma region Report

void UHSReportBaseWidget::CancelReport()
{
	ReportCancelEvent.Broadcast();
}

void UHSReportBaseWidget::StartAnomalyReport()
{
	TArray<UUserWidget*> FoundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHSInGameBase::StaticClass(), false);

	if (FoundWidgets.Num() <= 0)
	{
		return;
	}

	Cast<UHSInGameBase>(FoundWidgets[0])->ReportingTextTimer();
}

#pragma endregion

#pragma region Interface

void UHSReportBaseWidget::EscapeCurrentWidget()
{
	CancelReport();
}

void UHSReportBaseWidget::EnterCurrentWidget()
{
	StartAnomalyReport();
	UHSGameInstance* GameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->SetCurrentOpenWidget(nullptr);
}

#pragma endregion