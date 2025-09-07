// Made by LSH

#include "GameSystem/GameMode/HSGameMode.h"
#include "GameSystem/GameInstance/HSGameInstance.h"
#include "Player/Character/HSPlayer.h"
#include "Player/Controller/HSPlayerController.h"
#include "Player/State/HSPlayerState.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/Base/InGame/UI_InGame.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DirectionalLight.h"

#pragma region Base

void AHSGameMode::BeginPlay()
{
	Super::BeginPlay();

	bUseSeamlessTravel = false;

	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenBaseWidget(InGameClass, EInputModeType::GameOnly);

	GetWorld()->GetTimerManager().SetTimer(PlayTimeHandle, this, &ThisClass::IncreasePlayTime, 0.5f, true);

	TimeStop.RemoveDynamic(this, &ThisClass::StopPlayTime);
	TimeStop.AddDynamic(this, &ThisClass::StopPlayTime);
	TimeStop.RemoveDynamic(this, &ThisClass::TimeStopDuration);
	TimeStop.AddDynamic(this, &ThisClass::TimeStopDuration);
	TimeStop.RemoveDynamic(this, &ThisClass::StartTimePenalty);
	TimeStop.AddDynamic(this, &ThisClass::StartTimePenalty);
	TimeStop.RemoveDynamic(this, &ThisClass::TimeStopEffect);
	TimeStop.AddDynamic(this, &ThisClass::TimeStopEffect);
}

void AHSGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(PlayTimeHandle);
	GetWorld()->GetTimerManager().ClearTimer(DecreaseHandle);
	GetWorld()->GetTimerManager().ClearTimer(EffectHandle);

	Super::EndPlay(EndPlayReason);
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

void AHSGameMode::StopPlayTime(bool bIsStop)
{
	if (bIsStop)
	{
		GetWorld()->GetTimerManager().ClearTimer(PlayTimeHandle);
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(PlayTimeHandle, this, &ThisClass::IncreasePlayTime, 0.5f, true);
}

void AHSGameMode::TimeStopDuration(bool bIsStop)
{
	if (!bIsStop)
	{
		return;
	}

	FTimerHandle TimeStopHandle;
	GetWorld()->GetTimerManager().SetTimer(TimeStopHandle, [this]()
		{
			TimeStop.Broadcast(false);
		}, 60, false);
}

#pragma endregion

#pragma region Penalty

void AHSGameMode::GivePenalty()
{
	TargetDecrease += 80;
}

void AHSGameMode::StartTimePenalty(bool bIsStop)
{
	if (bIsStop)
	{
		return;
	}

	float CurrentDecrease = 0;

	GetWorld()->GetTimerManager().SetTimer(DecreaseHandle, [this, CurrentDecrease]() mutable
		{
			CurrentPlayTime -= 0.4f;
			CurrentDecrease += 0.4f;

			if (bOnCenter)
			{
				PlayTime.Broadcast(GetCurrentHour(), GetCurrentMinute(), TEXT(":"));
			}
			else
			{
				PlayTime.Broadcast(GetCurrentHour(), GetCurrentMinute(), TEXT(" "));
			}

			bOnCenter = !bOnCenter;

			if (CurrentDecrease >= TargetDecrease)
			{
				TargetDecrease = 0;
				GetWorld()->GetTimerManager().ClearTimer(DecreaseHandle);
			}
		}, 0.01f, true);
}

#pragma endregion

#pragma region PostProcessing

void AHSGameMode::TimeStopEffect(bool bIsStop)
{
	TArray<AActor*> FoundLights;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADirectionalLight::StaticClass(), FoundLights);
	ADirectionalLight* DirectionalLight = Cast<ADirectionalLight>(FoundLights[0]);

	if (bIsStop)
	{
		TargetRadius = 10000;
		RadiusSpeed = 25;

		DirectionalLight->SetLightColor(FLinearColor(0, 0, 0));
	}
	else
	{
		TargetRadius = 0;
		RadiusSpeed = -50;

		DirectionalLight->SetLightColor(FLinearColor(0, 0.04f, 0.04f));
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APostProcessVolume::StaticClass(), FoundActors);
	APostProcessVolume* PostProcessVolume = Cast<APostProcessVolume>(FoundActors[0]);

	UMaterialInstanceDynamic* StopDynMat = UMaterialInstanceDynamic::Create(StopEffectMat, this);
	FVector StartLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();

	PostProcessVolume->bUnbound = true;
	PostProcessVolume->Settings.WeightedBlendables.Array.Empty();
	PostProcessVolume->Settings.WeightedBlendables.Array.Add(FWeightedBlendable(1, StopDynMat));

	StopDynMat->SetVectorParameterValue(TEXT("Center"), FLinearColor(StartLocation.X, StartLocation.Y, StartLocation.Z, 0));

	GetWorld()->GetTimerManager().SetTimer(EffectHandle, [this, StopDynMat]() mutable
		{
			float SmoothRadius = CurrentRadius + RadiusSpeed;
			StopDynMat->SetScalarParameterValue(TEXT("Radius"), SmoothRadius);
			CurrentRadius = SmoothRadius;

			if (FMath::IsNearlyEqual(SmoothRadius, TargetRadius, 1))
			{
				GetWorld()->GetTimerManager().ClearTimer(EffectHandle);
			}
		}, 0.01f, true);
}

#pragma endregion