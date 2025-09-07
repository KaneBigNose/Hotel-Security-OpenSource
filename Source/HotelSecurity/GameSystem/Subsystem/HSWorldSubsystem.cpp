// Made by LSH

#include "GameSystem/Subsystem/HSWorldSubsystem.h"
#include "GameSystem/GameMode/HSGameMode.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "Spawner/Anomaly/HSSpawner_Anomaly.h"
#include "Spawner/Monster/HSSpawner_Monster.h"
#include "Anomaly/HSAnomalyBase.h"
#include "Data/Spawn/Anomaly/SpawnInfo_Anomaly.h"
#include "Data/Spawn/Monster/SpawnInfo_Monster.h"
#include "Player/Character/HSPlayer.h"
#include "UI/PopUp/InGame/Report/UI_Report.h"

#pragma region Base

void UHSWorldSubsystem::Deinitialize()
{
	if (Spawner_Anomaly && Spawner_Monster)
	{
		Spawner_Anomaly->Destroy();
		Spawner_Monster->Destroy();
	}

	UUI_Report::bCanReport = true;

	Super::Deinitialize();
}

void UHSWorldSubsystem::MapSetting()
{
	HSPlayer = Cast<AHSPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	ASC = Cast<UHSAbilitySystemComponent>(HSPlayer->GetAbilitySystemComponent());

	SpawnMapSpawner();

	FTimerHandle WaitAnomalyEventHandle;
	GetWorld()->GetTimerManager().SetTimer(WaitAnomalyEventHandle, this, &ThisClass::AnomalyEventTimer, WaitAnomalyDuration, false);

	AHSGameMode* GameMode = GetWorld()->GetAuthGameMode<AHSGameMode>();
	GameMode->TimeStop.RemoveDynamic(this, &ThisClass::StopAnomalyEvent);
	GameMode->TimeStop.AddDynamic(this, &ThisClass::StopAnomalyEvent);
}

#pragma endregion

#pragma region Data

UDataTable* UHSWorldSubsystem::GetAnomalyDataTable()
{
	return Spawner_Anomaly->GetSpawnDataTable();
}

UDataTable* UHSWorldSubsystem::GetRespawnDataTable()
{
	return Spawner_Monster->GetSpawnDataTable();
}

FSpawnInfo_Anomaly* UHSWorldSubsystem::GetAnomalyData(int32 RowNum, EMapType CurrentMap)
{
	return (FSpawnInfo_Anomaly*)Spawner_Anomaly->GetObjectData(RowNum, CurrentMap);
}

FSpawnInfo_Anomaly* UHSWorldSubsystem::GetAnomalyData(FString TargetName, FString TargetPlace)
{
	return (FSpawnInfo_Anomaly*)Spawner_Anomaly->GetObjectData(TargetName, TargetPlace);
}

FSpawnInfo_Monster* UHSWorldSubsystem::GetMonsterData(int32 RowNum, EMapType CurrentMap)
{
	return (FSpawnInfo_Monster*)Spawner_Monster->GetObjectData(RowNum, CurrentMap);
}

FSpawnInfo_Monster* UHSWorldSubsystem::GetMonsterData(FString TargetName)
{
	return (FSpawnInfo_Monster*)Spawner_Monster->GetObjectData(TargetName);
}

#pragma endregion

#pragma region Spawner

void UHSWorldSubsystem::SpawnMapSpawner()
{
	FString AnoPath = TEXT("/Game/HotelSecurity/Spawner/Blueprint/BP_Spawner_Anomaly.BP_Spawner_Anomaly_C");
	FString MonPath = TEXT("/Game/HotelSecurity/Spawner/Blueprint/BP_Spawner_Monster.BP_Spawner_Monster_C");

	TSubclassOf<AHSSpawner_Anomaly> AnoClass = StaticLoadClass(AHSSpawner_Anomaly::StaticClass(), nullptr, *AnoPath);
	TSubclassOf<AHSSpawner_Monster> MonClass = StaticLoadClass(AHSSpawner_Monster::StaticClass(), nullptr, *MonPath);

	Spawner_Anomaly = GetWorld()->SpawnActor<AHSSpawner_Anomaly>(AnoClass, FVector::ZeroVector, FRotator::ZeroRotator);
	Spawner_Monster = GetWorld()->SpawnActor<AHSSpawner_Monster>(MonClass, FVector::ZeroVector, FRotator::ZeroRotator);
}

#pragma endregion

#pragma region Anomaly Event

void UHSWorldSubsystem::StopAnomalyEvent(bool bIsStop)
{
	if (bIsStop)
	{
		GetWorld()->GetTimerManager().ClearTimer(AnomalyEventHandle);
		return;
	}

	AnomalyEventTimer();
}

void UHSWorldSubsystem::AnomalyEventTimer()
{
	int32 RandomTime = FMath::RandRange(-20, 20);

	GetWorld()->GetTimerManager().SetTimer(AnomalyEventHandle, this, &ThisClass::StartAnomalyEvent, DefaultAnomalyDuration + RandomTime, false);
}

void UHSWorldSubsystem::StartAnomalyEvent()
{
	TArray<AActor*> SpawnedAnomalys = Spawner_Anomaly->GetSpawnedObjects();
	int32 RandomIndex = FMath::RandRange(1, SpawnedAnomalys.Num());

	AHSAnomalyBase* Target = Cast<AHSAnomalyBase>(SpawnedAnomalys[RandomIndex - 1]);

	if (!Target->bApplyEvent)
	{
		StartAnomalyEvent();
		return;
	}

	CheckAnomalyCount();

	Target->StartRandomAnomaly(RandomIndex);

	AnomalyEventTimer();
	AnomalyEventOccur.Broadcast(CurrentAnomaly, MaxAnomaly);
}

void UHSWorldSubsystem::CheckAnomalyCount()
{
	if (++CurrentAnomaly < MaxAnomaly)
	{
		return;
	}

	ASC->AddUniqueGameplayTag(HSGameplayTags::State::Fired);
	HSPlayer->PlayerDie.Broadcast(nullptr);
}

#pragma endregion

#pragma region Anomaly Fix

void UHSWorldSubsystem::SucceedFixAnomaly()
{
	if (CurrentAnomaly > 0)
	{
		CurrentAnomaly--;
		FailCount = 0;
	}
}

void UHSWorldSubsystem::FailedFixAnomaly()
{
	if (++FailCount >= MaxFailCount)
	{
		ASC->AddUniqueGameplayTag(HSGameplayTags::State::Fired);
		HSPlayer->PlayerDie.Broadcast(nullptr);
	}
}

#pragma endregion