// Made by LSH

#include "UI/Report/Button/HSReportListAnomalyButton.h"
#include "UI/Report/HSReportBaseWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/HSGameInstance.h"
#include "Localization/LocalizationBase.h"
#include "Subsystem/Hotel/HotelSubsystem.h"
#include "Subsystem/Mine/MineSubsystem.h"
#include "Subsystem/Hospital/HospitalSubsystem.h"

void UHSReportListAnomalyButton::SetSelectedValueText()
{
	Super::SetSelectedValueText();

	ReportBaseWidget->SelectedAnomaly = AnomalyValue;

	UHSGameInstance* GameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	UHSWorldSubsystem* MapSubsystem = GetWorld()->GetSubsystem<UHSWorldSubsystem>();

	if (GameInstance->GetSelectedMapName() == FName("Hotel"))
	{
		MapSubsystem = GetWorld()->GetSubsystem<UHotelSubsystem>();
	}
	else if (GameInstance->GetSelectedMapName() == FName("Mine"))
	{
		MapSubsystem = GetWorld()->GetSubsystem<UMineSubsystem>();
	}
	else if (GameInstance->GetSelectedMapName() == FName("Hospital"))
	{
		MapSubsystem = GetWorld()->GetSubsystem<UHospitalSubsystem>();
	}

	FString CurrentString;

	FString PlaceInfo_En = MapSubsystem->GetLocalizationLocationData(ReportBaseWidget->SelectedLocation)->English;
	FString ObjectInfo_En = MapSubsystem->GetAnomalyData(ReportBaseWidget->SelectedObject)->English;
	FString AnomalyInfo_En = MapSubsystem->GetLocalizationAnomalyData(ReportBaseWidget->SelectedAnomaly)->English;

	FString PlaceInfo_Ko = MapSubsystem->GetLocalizationLocationData(ReportBaseWidget->SelectedLocation)->Korean;
	FString ObjectInfo_Ko = MapSubsystem->GetAnomalyData(ReportBaseWidget->SelectedObject)->Korean;
	FString AnomalyInfo_Ko = MapSubsystem->GetLocalizationAnomalyData(ReportBaseWidget->SelectedAnomaly)->Korean;

	if (GameInstance->GetSelectedLanguage() == FName("English"))
	{
		CurrentString = FString::Printf(TEXT("Place: %s | Object: %s | Anomaly: %s"), *PlaceInfo_En, *ObjectInfo_En, *AnomalyInfo_En);
	}
	else if (GameInstance->GetSelectedLanguage() == FName("Korean"))
	{
		CurrentString = FString::Printf(TEXT("장소: %s | 사물: %s | 이상 현상: %s"), *PlaceInfo_Ko, *ObjectInfo_Ko, *AnomalyInfo_Ko);
	}

	ReportBaseWidget->GetSelectedValueTextBlock()->SetText(FText::FromString(CurrentString));
}