// Made by LSH

#include "UI/PopUp/InGame/Report/UI_Report.h"
#include "UI/Button/Report/UI_Button_Report.h"
#include "GameSystem/GameInstance/HSGameInstance.h"
#include "GameSystem/Subsystem/HSWorldSubsystem.h"
#include "GameSystem/Enum/HSEnumManager.h"
#include "GameSystem/GameSave/HSSave_Report.h"
#include "Data/Spawn/Anomaly/SpawnInfo_Anomaly.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/Image.h"
#include "Anomaly/HSAnomalyBase.h"
#include "Spawner/Anomaly/HSSpawner_Anomaly.h"
#include "Blueprint/WidgetTree.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "UI_Report"

#pragma region Base

FReportStart UUI_Report::ReportStart;
bool UUI_Report::bCanReport = true;

void UUI_Report::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ReportButton->OnClicked.AddDynamic(this, &ThisClass::InputWidget_Enter);
	CancelButton->OnClicked.AddDynamic(this, &ThisClass::InputWidget_ESC);

	GameInstance = GetWorld()->GetGameInstance<UHSGameInstance>();
	Subsystem = GetWorld()->GetSubsystem<UHSWorldSubsystem>();

	SettingNames();

	CreateButtons(PlaceNames, PlaceButtons, PlaceScroll, EButtonValueType::Place);
	CreateButtons(ObjectNames, ObjectButtons, ObjectScroll, EButtonValueType::Object);
	CreateButtons(AnomalyNames, AnomalyButtons, AnomalyScroll, EButtonValueType::Anomaly);
}

void UUI_Report::NativeConstruct()
{
	Super::NativeConstruct();

	PreviewImageRendering();
	ReportingHighlight();
	SetRemainChanceImage();
}

#pragma endregion

#pragma region Highlight

void UUI_Report::ReportingHighlight()
{
	if (bCanReport)
	{
		return;
	}

	UHSSave_Report* Save_Report = Cast<UHSSave_Report>(UGameplayStatics::LoadGameFromSlot(TEXT("HSSave_Report"), 0));
	Save_Report->LoadReportData(SelectedPlaceIndex, SelectedObjectIndex, SelectedAnomalyIndex);

	Highlight(PlaceButtons, SelectedPlaceIndex);
	Highlight(ObjectButtons, SelectedObjectIndex);
	Highlight(AnomalyButtons, SelectedAnomalyIndex);

	ReportButton->SetVisibility(ESlateVisibility::Hidden);
}

#pragma endregion

#pragma region Report Button

void UUI_Report::SettingNames()
{
	FName CurrentMapName = HSEnumManager::GetEnumAsFName<EMapType>(GameInstance->SelectedMap);

	for (int32 Index = 1; Index <= Subsystem->GetAnomalyDataTable()->GetRowMap().Num(); Index++)
	{
		FSpawnInfo_Anomaly* Data = Subsystem->GetAnomalyData(Index);

		if (Data->Map_En != CurrentMapName)
		{
			continue;
		}

		if (GameInstance->SelectedLanguage == ELanguageType::English)
		{
			PlaceNames.AddUnique(Data->Place_En);
			ObjectNames.Add(Data->Object_En);
		}
		else if (GameInstance->SelectedLanguage == ELanguageType::Korean)
		{
			PlaceNames.AddUnique(Data->Place_Ko);
			ObjectNames.Add(Data->Object_Ko);
		}
	}
	
	AnomalyNames.Add(LOCTEXT("key1", "Move").ToString());
	AnomalyNames.Add(LOCTEXT("key2", "Rotate").ToString());
	AnomalyNames.Add(LOCTEXT("key3", "Expand").ToString());
	AnomalyNames.Add(LOCTEXT("key4", "Shrink").ToString());
	AnomalyNames.Add(LOCTEXT("key5", "Disappear").ToString());
	AnomalyNames.Add(LOCTEXT("key6", "Change").ToString());
	AnomalyNames.Add(LOCTEXT("key7", "Fly").ToString());
	AnomalyNames.Add(LOCTEXT("key8", "Darkness").ToString());
	AnomalyNames.Add(LOCTEXT("key9", "Ghost").ToString());
}

void UUI_Report::CreateButtons(const TArray<FString>& Names, TArray<TObjectPtr<UButton>>& HighlightGroup, UScrollBox* Scrollbox, EButtonValueType ValueType)
{
	for (int32 Index = 0; Index < Names.Num(); Index++)
	{
		UUI_Button_Report* NewButton = WidgetTree->ConstructWidget<UUI_Button_Report>(UUI_Button_Report::StaticClass());
		SettingListButtonStyle(NewButton);

		UTextBlock* ButtonText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());

		FString SettingName = Names[Index];

		ButtonText->SetText(FText::FromString(SettingName));
		ButtonText->SetJustification(ETextJustify::Center);

		NewButton->ButtonIndex = Index;
		NewButton->SetOwnerThisButton(this);
		NewButton->AddChild(ButtonText);

		switch (ValueType)
		{
		case EButtonValueType::Place:
			NewButton->PlaceValue = SettingName;
			break;

		case EButtonValueType::Object:
			NewButton->ObjectValue = SettingName;
			NewButton->ObjectIndex = Index + 1;
			break;

		case EButtonValueType::Anomaly:
			NewButton->AnomalyValue = SettingName;
			break;
		}

		HighlightGroup.Add(NewButton);

		Scrollbox->AddChild(NewButton);
	}
}

void UUI_Report::SettingListButtonStyle(UUI_Button_Report* NewButton)
{
	FButtonStyle NewButtonStyle;
	NewButtonStyle.Normal.TintColor = FSlateColor(FLinearColor(1, 1, 1, 0));
	NewButtonStyle.Hovered.TintColor = FSlateColor(FLinearColor(1, 1, 1, 0.3f));
	NewButtonStyle.Pressed.TintColor = FSlateColor(FLinearColor(1, 1, 1, 0.5f));
	NewButton->SetStyle(NewButtonStyle);
}

#pragma endregion

#pragma region Preview

void UUI_Report::PreviewImageRendering()
{
	UKismetRenderingLibrary::ClearRenderTarget2D(GetWorld(), ObjectPreview, FLinearColor::Black);

	UMaterialInstanceDynamic* DynMat = UMaterialInstanceDynamic::Create(ObjectPreview_Mat, this);
	DynMat->SetTextureParameterValue("RenderTarget", ObjectPreview);
	PreviewImage->SetBrushFromMaterial(DynMat);
}

#pragma endregion

#pragma region Remain Chance

void UUI_Report::SetRemainChanceImage()
{
	FSlateBrush RemainBrush, DeadBrush;

	RemainBrush.SetResourceObject(RemainChance);
	DeadBrush.SetResourceObject(DeadChance);

	switch (Subsystem->FailCount)
	{
	case 0:
		Chance1->SetBrush(RemainBrush);
		Chance2->SetBrush(RemainBrush);
		Chance3->SetBrush(RemainBrush);
		break;

	case 3:
		Chance3->SetBrush(DeadBrush);

	case 2:
		Chance2->SetBrush(DeadBrush);

	case 1:
		Chance1->SetBrush(DeadBrush);
	}
}

#pragma endregion

#pragma region Input

void UUI_Report::InputWidget_Enter()
{
	if (SelectedPlace.IsEmpty() || SelectedObject.IsEmpty() || SelectedAnomaly.IsEmpty())
	{
		return;
	}

	if (!bCanReport)
	{
		return;
	}

	bCanReport = false;

	ReportStart.Broadcast(SelectedPlace, SelectedObject, SelectedAnomaly);

	UHSSave_Report* Save_Report = Cast<UHSSave_Report>(UGameplayStatics::LoadGameFromSlot(TEXT("HSSave_Report"), 0));
	Save_Report->SaveReportData(SelectedPlaceIndex, SelectedObjectIndex, SelectedAnomalyIndex);

	InputWidget_ESC();
}

#pragma endregion

#undef LOCTEXT_NAMESPACE