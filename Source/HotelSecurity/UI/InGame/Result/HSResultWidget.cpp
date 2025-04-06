// Made by LSH

#include "UI/InGame/Result/HSResultWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "GameInstance/HSGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/Hotel/HotelSubsystem.h"
#include "Subsystem/Mine/MineSubsystem.h"
#include "Subsystem/Hospital/HospitalSubsystem.h"

#pragma region Base

UHSResultWidget::UHSResultWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SetVisibility(ESlateVisibility::Hidden);
}

#pragma endregion

#pragma region Report

void UHSResultWidget::ShowReportResultImage(bool bSuccessed)
{
	SetVisibility(ESlateVisibility::Visible);

	UHSWorldSubsystem* Subsystem = GetWorld()->GetSubsystem<UHSWorldSubsystem>();
	UHSGameInstance* GameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	FString MapName = FPaths::GetCleanFilename(GetWorld()->GetMapName());
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

	if (Subsystem->GetFailCount() >= Subsystem->GetMaxFailCount())
	{
		return;
	}

	if (bSuccessed)
	{
		if (GameInstance->GetSelectedLanguage() == FName("English"))
		{
			FString PrintMessage = TEXT("Anomaly Fixed");
			ResultText->SetText(FText::FromString(PrintMessage));
		}
		else if (GameInstance->GetSelectedLanguage() == FName("Korean"))
		{
			FString PrintMessage = TEXT("이상 현상 수정");
			ResultText->SetText(FText::FromString(PrintMessage));
		}
	}
	else
	{
		if (GameInstance->GetSelectedLanguage() == FName("English"))
		{
			FString PrintMessage = TEXT("Not Found Anomaly");
			ResultText->SetText(FText::FromString(PrintMessage));
		}
		else if (GameInstance->GetSelectedLanguage() == FName("Korean"))
		{
			FString PrintMessage = TEXT("이상 현상 없음");
			ResultText->SetText(FText::FromString(PrintMessage));
		}
	}

	GetWorld()->GetTimerManager().SetTimer(RemoveImageHandle, this, &ThisClass::RemoveReportImage, RemoveImageDuration, false);
}

void UHSResultWidget::RemoveReportImage()
{
	SetVisibility(ESlateVisibility::Hidden);
}

#pragma endregion