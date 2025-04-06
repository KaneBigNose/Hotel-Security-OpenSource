// Made by LSH

#include "UI/InGame/AnomalyEvent/HSAnomalyEventWidget.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"
#include "Components/AudioComponent.h"
#include "Components/TextBlock.h"
#include "Subsystem/Hotel/HotelSubsystem.h"
#include "Subsystem/Mine/MineSubsystem.h"
#include "Subsystem/Hospital/HospitalSubsystem.h"
#include "GameInstance/HSGameInstance.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

void UHSAnomalyEventWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FString MapName = FPaths::GetCleanFilename(GetWorld()->GetMapName());

	if (MapName.EndsWith(TEXT("Hotel")))
	{
		Subsystem = GetWorld()->GetSubsystem<UHotelSubsystem>();
		Subsystem->AnomalyEventOccur.AddDynamic(this, &ThisClass::OccurAnomalyEvent);
	}
	else if (MapName.EndsWith(TEXT("Mine")))
	{
		Subsystem = GetWorld()->GetSubsystem<UMineSubsystem>();
		Subsystem->AnomalyEventOccur.AddDynamic(this, &ThisClass::OccurAnomalyEvent);
	}
	else if (MapName.EndsWith(TEXT("Hospital")))
	{
		Subsystem = GetWorld()->GetSubsystem<UHospitalSubsystem>();
		Subsystem->AnomalyEventOccur.AddDynamic(this, &ThisClass::OccurAnomalyEvent);
	}

	GameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	SetVisibility(ESlateVisibility::Hidden);
}

#pragma endregion

#pragma region Widget

void UHSAnomalyEventWidget::OccurAnomalyEvent()
{
	if (Subsystem->GetCurrentAnomaly() < 4)
	{
		if (GameInstance->GetSelectedLanguage() == FName("English"))
		{
			FString PrintMessage = TEXT("Anomaly Occurrence");
			CurrentText->SetText(FText::FromString(PrintMessage));
		}
		else if (GameInstance->GetSelectedLanguage() == FName("Korean"))
		{
			FString PrintMessage = TEXT("이상 현상 발생");
			CurrentText->SetText(FText::FromString(PrintMessage));
		}
	}
	else if (Subsystem->GetCurrentAnomaly() == 4)
	{
		if (GameInstance->GetSelectedLanguage() == FName("English"))
		{
			FString PrintMessage = TEXT("Anomaly Warning");
			CurrentText->SetText(FText::FromString(PrintMessage));
		}
		else if (GameInstance->GetSelectedLanguage() == FName("Korean"))
		{
			FString PrintMessage = TEXT("이상 현상 경고");
			CurrentText->SetText(FText::FromString(PrintMessage));
		}
	}

	SetVisibility(ESlateVisibility::Visible);

	GetWorld()->GetTimerManager().SetTimer(AnomalyEventHandle, this, &ThisClass::AnomalyEventUIClear, AnomalyUIDuration, false);
}

void UHSAnomalyEventWidget::AnomalyEventUIClear()
{
	SetVisibility(ESlateVisibility::Hidden);
}

#pragma endregion