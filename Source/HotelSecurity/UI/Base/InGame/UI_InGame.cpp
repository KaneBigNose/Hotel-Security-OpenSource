// Made by LSH

#include "UI/Base/InGame/UI_InGame.h"
#include "UI/PopUp/InGame/Result/UI_Result.h"
#include "UI/PopUp/InGame/Report/UI_Report.h"
#include "UI/Controller/UI_Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Character/Component/Interact/HSCharacterInteract.h"
#include "GameSystem/Subsystem/HSWorldSubsystem.h"
#include "GameSystem/GameMode/HSGameMode.h"
#include "Data/Spawn/Anomaly/SpawnInfo_Anomaly.h"
#include "Anomaly/HSAnomalyBase.h"
#include "Player/Character/HSPlayer.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/AttributeSet/Player/HSPlayerAttributeSet.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "GAS/AbilityTask/Flash/AT_ConsumeBattery.h"
#include "Spawner/Anomaly/HSSpawner_Anomaly.h"

#define LOCTEXT_NAMESPACE "UI_InGame"

#pragma region Base

void UUI_InGame::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AHSPlayer* HSPlayer = Cast<AHSPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(HSPlayer->GetAbilitySystemComponent());

	Subsystem = GetWorld()->GetSubsystem<UHSWorldSubsystem>();
	UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();

	HSPlayer->GetInteractComponent()->CanInteract.AddDynamic(this, &ThisClass::ChangeAim);
	AimCanvasSlot = Cast<UCanvasPanelSlot>(AimImage->Slot);

	Subsystem->AnomalyEventOccur.AddDynamic(this, &ThisClass::OccurAnomalyEvent);
	AnomalyEventImage->SetVisibility(ESlateVisibility::Hidden);
	AnomalyEventBack->SetVisibility(ESlateVisibility::Hidden);
	AnomalyEventText->SetVisibility(ESlateVisibility::Hidden);

	ASC->BindAttributeChange<UUI_InGame>(EBindDataType::FlashLife, this, &UUI_InGame::UpdateBattery, PlayerAS);
	UAT_ConsumeBattery::FlashAction.AddDynamic(this, &ThisClass::SetVisibleBattery);
	FlashBatteryBar->SetVisibility(ESlateVisibility::Hidden);

	FearBar->SetVisibility(ESlateVisibility::Hidden);
	ASC->BindAttributeChange<UUI_InGame>(EBindDataType::FearGage, this, &UUI_InGame::UpdateFearBar, PlayerAS);

	Cast<AHSGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->PlayTime.AddDynamic(this, &ThisClass::SetPlayTimeText);

	UUI_Report::ReportStart.AddDynamic(this, &ThisClass::ShowReportingResult);

	ReportingText->SetVisibility(ESlateVisibility::Hidden);
}

#pragma endregion

#pragma region Aim

void UUI_InGame::ChangeAim(bool bCanInteract)
{
	FSlateBrush Brush;

	if (bCanInteract)
	{
		Brush.SetResourceObject(InteractTexture);
		AimCanvasSlot->SetPosition(FVector2D(-12, -12));
		AimCanvasSlot->SetSize(FVector2D(24, 24));
	}
	else
	{
		Brush.SetResourceObject(NormalTexture);
		AimCanvasSlot->SetPosition(FVector2D(-3, -3));
		AimCanvasSlot->SetSize(FVector2D(6, 6));
	}

	Brush.SetImageSize(FVector2d(100, 100));
	AimImage->SetBrush(Brush);
}

#pragma endregion

#pragma region AnomalyEvent

void UUI_InGame::OccurAnomalyEvent(int32 CurrentAnomaly, const int32 MaxAnomaly)
{
	if (CurrentAnomaly >= MaxAnomaly)
	{
		return;
	}

	if (CurrentAnomaly < MaxAnomaly - 1)
	{
		FText PrintMessage = LOCTEXT("key1", "Anomaly Occurrence");
		AnomalyEventText->SetText(PrintMessage);
	}
	else if (CurrentAnomaly == MaxAnomaly - 1)
	{
		FText PrintMessage = LOCTEXT("key2", "Anomaly Warning");
		AnomalyEventText->SetText(PrintMessage);
	}

	AnomalyEventImage->SetVisibility(ESlateVisibility::Visible);
	AnomalyEventBack->SetVisibility(ESlateVisibility::Visible);
	AnomalyEventText->SetVisibility(ESlateVisibility::Visible);

	FTimerHandle AnomalyEventHandle;
	GetWorld()->GetTimerManager().SetTimer(AnomalyEventHandle, [this]()
		{
			AnomalyEventImage->SetVisibility(ESlateVisibility::Hidden);
			AnomalyEventBack->SetVisibility(ESlateVisibility::Hidden);
			AnomalyEventText->SetVisibility(ESlateVisibility::Hidden);
		}, 3, false);
}

#pragma endregion

#pragma region Battery

void UUI_InGame::UpdateBattery(const FOnAttributeChangeData& Data)
{
	float CurrentBattery = PlayerAS->GetFlashLife();
	float MaxBattery = PlayerAS->GetMaxFlashLife();

	FlashBatteryBar->SetPercent(CurrentBattery / MaxBattery);
}

void UUI_InGame::SetVisibleBattery(bool bIsVisible)
{
	if (bIsVisible)
	{
		FlashBatteryBar->SetVisibility(ESlateVisibility::Visible);

		return;
	}

	FlashBatteryBar->SetVisibility(ESlateVisibility::Hidden);
}

#pragma endregion

#pragma region Fear

void UUI_InGame::UpdateFearBar(const FOnAttributeChangeData& Data)
{
	float CurrentValue = PlayerAS->GetFearGage();
	float MaxValue = PlayerAS->GetMaxFearGage();
	float CurrentPercentage = CurrentValue / MaxValue;

	if (CurrentPercentage > 0)
	{
		FearBar->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		FearBar->SetVisibility(ESlateVisibility::Hidden);
	}

	FearBar->SetPercent(CurrentPercentage);
}

#pragma endregion

#pragma region Play Time

void UUI_InGame::SetPlayTimeText(int32 Hour, int32 Minute, FString Center)
{
	FString TimeString = FString::Printf(TEXT("%02d %s %02d"), Hour, *Center, Minute);
	PlayTimeText->SetText(FText::FromString(TimeString));
}

#pragma endregion

#pragma region Report

void UUI_InGame::ShowReportingResult(FString SelectedLocation, FString SelectedObject, FString SelectedAnomaly)
{
	PrintMessage1 = LOCTEXT("key3", "Reporting");
	PrintMessage2 = LOCTEXT("key4", "Reporting.");
	PrintMessage3 = LOCTEXT("key5", "Reporting..");
	PrintMessage4 = LOCTEXT("key6", "Reporting...");

	ReportingText->SetText(PrintMessage1);
	ReportingText->SetVisibility(ESlateVisibility::Visible);

	GetWorld()->GetTimerManager().SetTimer(AnimationHandle, [this]()
		{
			switch (TextIndex)
			{
			case 1:
				ReportingText->SetText(PrintMessage1);
				TextIndex++;
				break;

			case 2:
				ReportingText->SetText(PrintMessage2);
				TextIndex++;
				break;

			case 3:
				ReportingText->SetText(PrintMessage3);
				TextIndex++;
				break;

			case 4:
				ReportingText->SetText(PrintMessage4);
				TextIndex = 1;
				break;
			}
		}, 0.5f, true);

	FTimerHandle ReportingTextHandle;
	GetWorld()->GetTimerManager().SetTimer(ReportingTextHandle, [this, SelectedLocation, SelectedObject, SelectedAnomaly]()
		{
			int32 SelectedNumber = Subsystem->GetAnomalyData(SelectedObject)->Number - 1;
			UUI_Result* ResultWidget = Cast<UUI_Result>(UICon->OpenPopUpWidget(ResultClass));
			ResultWidget->ShowReportResultImage(Cast<AHSAnomalyBase>(Subsystem->GetAnomalySpawner()->GetSpawnedObjects()[SelectedNumber])->FixCurrentAnomaly(SelectedLocation, SelectedObject, SelectedAnomaly));

			ReportingText->SetVisibility(ESlateVisibility::Hidden);

			UUI_Report::bCanReport = true;

			GetWorld()->GetTimerManager().ClearTimer(AnimationHandle);
		}, 10, false);
}

#pragma endregion

#undef LOCTEXT_NAMESPACE