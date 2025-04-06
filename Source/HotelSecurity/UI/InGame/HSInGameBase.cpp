// Made by LSH

#include "UI/InGame/HSInGameBase.h"
#include "UI/InGame/Aim/HSAimWidget.h"
#include "UI/InGame/FlashBattery/HSFlashWidget.h"
#include "UI/InGame/AnomalyEvent/HSAnomalyEventWidget.h"
#include "UI/InGame/PlayTime/HSPlayTimeWidget.h"
#include "UI/Report/HSReportBaseWidget.h"
#include "UI/InGame/Result/HSResultWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "Player/HSPlayer/HSPlayerController.h"
#include "Player/Sound/HSPlayerSound.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanelSlot.h"
#include "Interact/Door/HSInteractDoor.h"
#include "Components/TextBlock.h"
#include "GAS/GameplayTag/HSPlayerGameplayTags.h"
#include "Subsystem/Hotel/HotelSubsystem.h"
#include "Subsystem/Mine/MineSubsystem.h"
#include "Subsystem/Hospital/HospitalSubsystem.h"
#include "Anomaly/Data/AnomalyInfoBase.h"
#include "Anomaly/HSAnomalyBase.h"

#pragma region Base

void UHSInGameBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    HSPlayer = Cast<AHSPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    UCanvasPanelSlot* FlashWidgetCanvasSlot = Cast<UCanvasPanelSlot>(FlashWidget->Slot);
    FlashWidgetCanvasSlot->SetPosition(FVector2D(0, -200));
    FlashWidgetCanvasSlot->SetSize(FVector2D(120, 240));

    UCanvasPanelSlot* AnomalyEventWidgetCanvasSlot = Cast<UCanvasPanelSlot>(AnomalyEventWidget->Slot);
    AnomalyEventWidgetCanvasSlot->SetPosition(FVector2D(-575, 110));
    AnomalyEventWidgetCanvasSlot->SetSize(FVector2D(1150, 220));

    UCanvasPanelSlot* PlayTimeWidgetCanvasSlot = Cast<UCanvasPanelSlot>(PlayTimeWidget->Slot);
    PlayTimeWidgetCanvasSlot->SetPosition(FVector2D(-220, 60));
    PlayTimeWidgetCanvasSlot->SetSize(FVector2D(200, 50));

    UCanvasPanelSlot* ReportingTextBlockSlot = Cast<UCanvasPanelSlot>(ReportingTextBlock->Slot);
    ReportingTextBlockSlot->SetPosition(FVector2D(-225, -70));
    ReportingTextBlockSlot->SetSize(FVector2D(200, 50));
    ReportingTextBlock->Font.Size = 30.f;
    ReportingTextBlock->SetVisibility(ESlateVisibility::Hidden);
}

#pragma endregion

#pragma region Report

void UHSInGameBase::ReportingTextTimer()
{
    ReportingTextBlock->SetVisibility(ESlateVisibility::Visible);

    Cast<AHSPlayerController>(HSPlayer->GetController())->ResetReportUI();

    GetWorld()->GetTimerManager().SetTimer(ReportingTextHandle, this, &ThisClass::SetReportingTextUnVisible, ReportingDuration, false);
}

void UHSInGameBase::SetReportingTextUnVisible()
{
    ReportingTextBlock->SetVisibility(ESlateVisibility::Hidden);

    HSPlayer->GetHSPlayerStateContainer().RemoveTag(HSPlayerGameplayTags::HSPlayer_State_Report);

    TArray<UUserWidget*> FoundWidgets;

    UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHSReportBaseWidget::StaticClass(), false);

    UHSReportBaseWidget* ReportBaseWidget = Cast<UHSReportBaseWidget>(FoundWidgets[0]);

    FString MapName = FPaths::GetCleanFilename(GetWorld()->GetMapName());

    UHSWorldSubsystem* Subsystem = GetWorld()->GetSubsystem<UHSWorldSubsystem>();

    if (MapName.EndsWith(TEXT("Hotel")))
    {
        Subsystem = GetWorld()->GetSubsystem<UHotelSubsystem>();
    }
    else if (MapName.EndsWith(TEXT("Mine")))
    {
        Subsystem = GetWorld()->GetSubsystem<UMineSubsystem>();
    }
    else if (MapName.EndsWith(TEXT("Hospital")))
    {
        Subsystem = GetWorld()->GetSubsystem<UHospitalSubsystem>();
    }

	int32 SelectedNumber = Subsystem->GetAnomalyData(FName(*ReportBaseWidget->SelectedObject.ToString()))->ActorNumber - 1;

    if (Subsystem->GetSpawnedAnomalys()[SelectedNumber]->FixCurrentAnomaly(ReportBaseWidget->SelectedLocation, ReportBaseWidget->SelectedObject, ReportBaseWidget->SelectedAnomaly))
    {
        ResultWidget->ShowReportResultImage(true);
    }
    else
    {
        ResultWidget->ShowReportResultImage(false);
    }

    HSPlayer->GetHSPlayerSoundComponent()->PlayAnomalyFixSound();
}

#pragma endregion

#pragma region Loading

void UHSInGameBase::LoadingComplete()
{
    LoadingWidget->SetVisibility(ESlateVisibility::Hidden);
}

#pragma endregion