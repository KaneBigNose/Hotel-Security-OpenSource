// Made by LSH

#include "UI/PopUp/InGame/Result/UI_Result.h"
#include "UI/Controller/UI_Controller.h"
#include "GameSystem/GameInstance/HSGameInstance.h"
#include "GameSystem/Subsystem/HSWorldSubsystem.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

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

	static float TotalTime = 0;

	TotalTime += InDeltaTime;

	if (TotalTime > 2)
	{
		ASC->RemoveLooseGameplayTag(HSGameplayTags::UI::PopUp::Report);

		UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
		UICon->ClosePopUpWidget(EInputModeType::GameOnly);
	}
}

#pragma endregion

#pragma region Report

void UUI_Result::ShowReportResultImage(bool bSuccessed)
{
	SetVisibility(ESlateVisibility::Visible);

	UHSGameInstance* GameInstance = GetWorld()->GetGameInstance<UHSGameInstance>();
	UHSWorldSubsystem* Subsystem = GetWorld()->GetSubsystem<UHSWorldSubsystem>();

	if (Subsystem->FailCount >= Subsystem->MaxFailCount)
	{
		return;
	}

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