// Made by LSH

#include "UI/PopUp/InGame/Result/UI_Result.h"
#include "UI/Controller/UI_Controller.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "Components/TextBlock.h"

#define LOCTEXT_NAMESPACE "UI_Result"

#pragma region Base

void UUI_Result::NativeConstruct()
{
	Super::NativeConstruct();

	HSPlayer = Cast<AHSPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	ASC = Cast<UHSAbilitySystemComponent>(HSPlayer->GetAbilitySystemComponent());

	ASC->AddUniqueGameplayTag(HSGameplayTags::UI::PopUp::Report);
}

void UUI_Result::NativeTick(FGeometry const& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	TotalTime += InDeltaTime;

	if (TotalTime > 2.5f)
	{
		ASC->RemoveLooseGameplayTag(HSGameplayTags::UI::PopUp::Report);

		UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
		UICon->ClosePopUpWidget(EInputModeType::GameOnly);

		TotalTime = 0;
	}
}

#pragma endregion

#pragma region Report

void UUI_Result::ShowReportResultImage(bool bSuccessed)
{
	SetVisibility(ESlateVisibility::Visible);

	FText PrintMessage;

	if (bSuccessed)
	{
		PrintMessage = LOCTEXT("key1", "Anomaly Fixed");
	}
	else
	{
		PrintMessage = LOCTEXT("key2", "Not Found Anomaly");
	}

	ResultText->SetText(PrintMessage);
}

#pragma endregion

#pragma region Input

void UUI_Result::InputWidget_ESC()
{

}

#pragma endregion

#undef LOCTEXT_NAMESPACE