// Made by LSH

#include "GameSystem/GameMode/HSGameMode.h"
#include "GameSystem/GameInstance/HSGameInstance.h"
#include "Player/Character/HSPlayer.h"
#include "Player/Controller/HSPlayerController.h"
#include "Player/State/HSPlayerState.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/Base/InGame/UI_InGame.h"

#pragma region Base

void AHSGameMode::BeginPlay()
{
	Super::BeginPlay();

	bUseSeamlessTravel = false;

	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenBaseWidget(InGameClass, EInputModeType::GameOnly);

	GetWorld()->GetTimerManager().SetTimer(PlayTimeHandle, this, &ThisClass::IncreasePlayTime, 0.5f, true);
}

#pragma endregion

#pragma region Timer

int32 AHSGameMode::GetCurrentHour()
{
	int32 CurrentHour = (CurrentPlayTime / InGameOneMinute) / 60 + 22;

	if (CurrentHour >= 24)
	{
		CurrentHour -= 24;
	}

	return CurrentHour;
}

int32 AHSGameMode::GetCurrentMinute()
{
	return (CurrentPlayTime / InGameOneMinute) % 60;
}

void AHSGameMode::IncreasePlayTime()
{
	if (CurrentPlayTime >= EndPlayTime)
	{
		GetWorld()->GetTimerManager().ClearTimer(PlayTimeHandle);

		UHSGameInstance* GameInstance = GetWorld()->GetGameInstance<UHSGameInstance>();
		GameInstance->StageClear.Broadcast();
	}
	else
	{
		CurrentPlayTime++;

		if (bOnCenter)
		{
			PlayTime.Broadcast(GetCurrentHour(), GetCurrentMinute(), TEXT(":"));
		}
		else
		{
			PlayTime.Broadcast(GetCurrentHour(), GetCurrentMinute(), TEXT(" "));
		}

		bOnCenter = !bOnCenter;
	}
}

#pragma endregion