// Made by LSH

#include "UI/Report/ReportList/HSReportList.h"
#include "UI/Report/Button/HSReportListLocationButton.h"
#include "UI/Report/Button/HSReportListObjectButton.h"
#include "UI/Report/Button/HSReportListAnomalyButton.h"
#include "UI/Report/HSReportBaseWidget.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/ButtonSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Subsystem/Hotel/HotelSubsystem.h"
#include "Subsystem/Mine/MineSubsystem.h"
#include "Subsystem/Hospital/HospitalSubsystem.h"
#include "Blueprint/WidgetTree.h"
#include "Enum/HSEnumManager.h"
#include "Anomaly/Data/AnomalyInfoBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/HSGameInstance.h"
#include "Localization/LocalizationBase.h"

#pragma region Base

UHSReportList::UHSReportList(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> ListButtonImageFinder(TEXT("/Game/HotelSecurity/UI/Texture/Report/Report_ListButton"));
	if (ListButtonImageFinder.Succeeded())
	{
		ListButtonImage = ListButtonImageFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> ListButtonImageOnMouseFinder(TEXT("/Game/HotelSecurity/UI/Texture/Report/Report_ListButton_OnMouse"));
	if (ListButtonImageOnMouseFinder.Succeeded())
	{
		ListButtonImageOnMouse = ListButtonImageOnMouseFinder.Object;
	}
}

void UHSReportList::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHSReportBaseWidget::StaticClass(), false);

	if (FoundWidgets.Num() > 0)
	{
		ReportBaseWidget = Cast<UHSReportBaseWidget>(FoundWidgets[0]);
	}

	SelectMapSubsystem();
	CreateAllButtons();
}

#pragma endregion

#pragma region Setting

void UHSReportList::SelectMapSubsystem()
{
	UWorld* CurrentWorld = GetWorld();

	if (!CurrentWorld)
	{
		return;
	}

	if (GameInstance->GetSelectedMapName() == FName("Hotel"))
	{
		MapSubsystem = GetWorld()->GetSubsystem<UHotelSubsystem>();
		LocationNames.Add(FName("Hotel_Private"));
		LocationNames.Add(FName("Hotel_Corridor"));
		LocationNames.Add(FName("Hotel_Reception"));
	}
	else if (GameInstance->GetSelectedMapName() == FName("Mine"))
	{
		MapSubsystem = GetWorld()->GetSubsystem<UMineSubsystem>();
		LocationNames.Add(FName("Zone_Red"));
		LocationNames.Add(FName("Zone_Yellow"));
		LocationNames.Add(FName("Zone_Green"));
		LocationNames.Add(FName("Zone_White"));
	}
	else if (GameInstance->GetSelectedMapName() == FName("Hospital"))
	{
		MapSubsystem = GetWorld()->GetSubsystem<UHospitalSubsystem>();
		LocationNames.Add(FName("Floor_1"));
		LocationNames.Add(FName("Floor_2"));
		LocationNames.Add(FName("Floor_3"));
	}

	if (!MapSubsystem)
	{
		return;
	}

	SettingFNameArray();
}

void UHSReportList::SettingFNameArray()
{
	for (int32 CurrentNum = 0; CurrentNum < MapSubsystem->GetAnomalyData()->GetRowMap().Num(); CurrentNum++)
	{
		if (ObjectNames.Contains(MapSubsystem->GetAnomalyData(CurrentNum + 1)->ActorName))
		{
			continue;
		}

		ObjectNames.Add(MapSubsystem->GetAnomalyData(CurrentNum + 1)->ActorName);
	}

	AnomalyNames.Add(HSEnumManager<EAnomalyType>::GetEnumAsFName(EAnomalyType::Location));
	AnomalyNames.Add(HSEnumManager<EAnomalyType>::GetEnumAsFName(EAnomalyType::Rotation));
	AnomalyNames.Add(HSEnumManager<EAnomalyType>::GetEnumAsFName(EAnomalyType::Scale));
	AnomalyNames.Add(HSEnumManager<EAnomalyType>::GetEnumAsFName(EAnomalyType::Disappear));
	AnomalyNames.Add(HSEnumManager<EAnomalyType>::GetEnumAsFName(EAnomalyType::Change));
	AnomalyNames.Add(HSEnumManager<EAnomalyType>::GetEnumAsFName(EAnomalyType::Fly));
}

#pragma endregion

#pragma region Create Button

void UHSReportList::CreateAllButtons()
{
	CreateLocationButtons();
	CreateObjectButtons();
	CreateAnomalyButtons();
}

void UHSReportList::CreateLocationButtons()
{
	for (int32 CurrentNum = 0; CurrentNum < LocationNames.Num(); CurrentNum++)
	{
		UHSReportListLocationButton* NewButton = WidgetTree->ConstructWidget<UHSReportListLocationButton>(UHSReportListLocationButton::StaticClass());
		SettingListButtonStyle(NewButton);

		UTextBlock* ButtonText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());

		FName LocationName = LocationNames[CurrentNum];
		FString LocalizationLocationName;

		if (GameInstance->GetSelectedLanguage() == FName("English"))
		{
			LocalizationLocationName = MapSubsystem->GetLocalizationLocationData(LocationName)->English;
		}
		else if (GameInstance->GetSelectedLanguage() == FName("Korean"))
		{
			LocalizationLocationName = MapSubsystem->GetLocalizationLocationData(LocationName)->Korean;
		}

		NewButton->SetLocationValue(LocationName);
		ButtonText->SetText(FText::FromString(LocalizationLocationName));
		ButtonText->SetJustification(ETextJustify::Center);

		NewButton->AddChild(ButtonText);
		NewButton->OnClicked.AddDynamic(NewButton, &UHSReportListLocationButton::SetSelectedValueText);

		LocationScrollBox->AddChild(NewButton);
		LocationButtons.Add(NewButton);
	}
}

void UHSReportList::CreateObjectButtons()
{
	for (int32 CurrentNum = 0; CurrentNum < ObjectNames.Num(); CurrentNum++)
	{
		UHSReportListObjectButton* NewButton = WidgetTree->ConstructWidget<UHSReportListObjectButton>(UHSReportListObjectButton::StaticClass());
		SettingListButtonStyle(NewButton);

		UTextBlock* ButtonText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());

		FName ObjectName = ObjectNames[CurrentNum];
		FString LocalizationObjectName;

		if (GameInstance->GetSelectedLanguage() == FName("English"))
		{
			LocalizationObjectName = MapSubsystem->GetAnomalyData(ObjectName)->English;
		}
		else if (GameInstance->GetSelectedLanguage() == FName("Korean"))
		{
			LocalizationObjectName = MapSubsystem->GetAnomalyData(ObjectName)->Korean;
		}

		NewButton->SetObjectValue(ObjectName);
		ButtonText->SetText(FText::FromString(LocalizationObjectName));
		ButtonText->SetJustification(ETextJustify::Center);

		NewButton->AddChild(ButtonText);
		NewButton->OnClicked.AddDynamic(NewButton, &UHSReportListObjectButton::SetSelectedValueText);

		ObjectScrollBox->AddChild(NewButton);
		ObjectButtons.Add(NewButton);
	}
}

void UHSReportList::CreateAnomalyButtons()
{
	for (int32 CurrentNum = 0; CurrentNum < AnomalyNames.Num(); CurrentNum++)
	{
		UHSReportListAnomalyButton* NewButton = WidgetTree->ConstructWidget<UHSReportListAnomalyButton>(UHSReportListAnomalyButton::StaticClass());
		SettingListButtonStyle(NewButton);

		UTextBlock* ButtonText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());

		FName AnomalyName = AnomalyNames[CurrentNum];
		FString LocalizationAnomalyName;

		if (GameInstance->GetSelectedLanguage() == FName("English"))
		{
			LocalizationAnomalyName = MapSubsystem->GetLocalizationAnomalyData(AnomalyName)->English;
		}
		else if (GameInstance->GetSelectedLanguage() == FName("Korean"))
		{
			LocalizationAnomalyName = MapSubsystem->GetLocalizationAnomalyData(AnomalyName)->Korean;
		}

		NewButton->SetAnomalyValue(AnomalyName);
		ButtonText->SetText(FText::FromString(LocalizationAnomalyName));
		ButtonText->SetJustification(ETextJustify::Center);

		NewButton->AddChild(ButtonText);
		NewButton->OnClicked.AddDynamic(NewButton, &UHSReportListAnomalyButton::SetSelectedValueText);

		AnomalyScrollBox->AddChild(NewButton);
		AnomalyButtons.Add(NewButton);
	}
}

void UHSReportList::SettingListButtonStyle(UHSReportListBaseButton* NewButton)
{
	FButtonStyle NewButtonStyle;
	NewButtonStyle.SetNormal(FSlateBrush());
	NewButtonStyle.Normal.SetResourceObject(ListButtonImage);
	NewButtonStyle.SetHovered(FSlateBrush());
	NewButtonStyle.Hovered.SetResourceObject(ListButtonImageOnMouse);
	NewButtonStyle.SetPressed(FSlateBrush());
	NewButtonStyle.Pressed.SetResourceObject(ListButtonImageOnMouse);
	NewButton->SetStyle(NewButtonStyle);
}

#pragma endregion