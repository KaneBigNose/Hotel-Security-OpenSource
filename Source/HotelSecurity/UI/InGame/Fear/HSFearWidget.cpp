// Made by LSH

#include "UI/InGame/Fear/HSFearWidget.h"
#include "Components/ProgressBar.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GAS/GameplayTag/HSPlayerGameplayTags.h"

#pragma region Base

UHSFearWidget::UHSFearWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UHSFearWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GetWorld()->GetTimerManager().SetTimer(FearHandle, this, &ThisClass::DecreaseFearValue, 1.f, true);
}

#pragma endregion

#pragma region Fear

void UHSFearWidget::IncreaseFearValue()
{
	CurrentFearValue = FMath::Clamp(CurrentFearValue + 25, 0.f, MaxFearValue);

	if (CurrentFearValue >= MaxFearValue)
	{
		AHSPlayer* HSPlayer = Cast<AHSPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		HSPlayer->GetHSPlayerStateContainer().AddTag(HSPlayerGameplayTags::HSPlayer_State_Fear);
		HSPlayer->PlayerDieDelegate.Broadcast(nullptr);
	}
}

void UHSFearWidget::IncreaseFearValue2()
{
	CurrentFearValue = FMath::Clamp(CurrentFearValue + 1.5f, 0.f, MaxFearValue);

	if (CurrentFearValue >= MaxFearValue)
	{
		AHSPlayer* HSPlayer = Cast<AHSPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		HSPlayer->GetHSPlayerStateContainer().AddTag(HSPlayerGameplayTags::HSPlayer_State_Fear);
		HSPlayer->PlayerDieDelegate.Broadcast(nullptr);
	}
}

void UHSFearWidget::DecreaseFearValue()
{
	if (CurrentFearValue > 0.f)
	{
		CurrentFearValue -= 0.5f;
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}

	FearBar->SetPercent(GetCurrentFearPercent());
}

#pragma endregion