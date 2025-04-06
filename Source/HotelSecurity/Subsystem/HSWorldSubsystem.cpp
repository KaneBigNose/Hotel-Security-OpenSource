// Made by LSH

#include "Subsystem/HSWorldSubsystem.h"
#include "AI/Data/Hotel/HotelRespawnInfo.h"
#include "Anomaly/Data/Hotel/HotelAnomalyInfo.h"
#include "Anomaly/HSAnomalyBase.h"
#include "AI/HSMonsterBase/HSMonsterBase.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Localization/LocalizationBase.h"

#pragma region Base

UHSWorldSubsystem::UHSWorldSubsystem()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> LocalizationLocationDataFinder(TEXT("/Game/HotelSecurity/Data/Report/DT_Location"));
	if (LocalizationLocationDataFinder.Succeeded())
	{
		LocalizationLocationData = LocalizationLocationDataFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> LocalizationAnomalyDataFinder(TEXT("/Game/HotelSecurity/Data/Report/DT_Anomaly"));
	if (LocalizationAnomalyDataFinder.Succeeded())
	{
		LocalizationAnomalyData = LocalizationAnomalyDataFinder.Object;
	}
}

void UHSWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	FString MapName = FPaths::GetCleanFilename(GetWorld()->GetMapName());
	if (MapName.EndsWith(TEXT("MainMenu")))
	{
		return;
	}

	AHSPlayer* HSPlayer = Cast<AHSPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	HSPlayer->PlayerDieDelegate.AddDynamic(this, &ThisClass::EndAnomalyEvent);
}

#pragma endregion

#pragma region Data

FAnomalyInfoBase* UHSWorldSubsystem::GetAnomalyData(int32 ActorNum)
{
	return AnomalyData->FindRow<FAnomalyInfoBase>(*FString::FromInt(ActorNum), TEXT(""));
}

FAnomalyInfoBase* UHSWorldSubsystem::GetAnomalyData(FName ActorName)
{
	FAnomalyInfoBase* AnomalyInfo = nullptr;

	for (auto RowData : AnomalyData->GetRowMap())
	{
		AnomalyInfo = (FAnomalyInfoBase*)RowData.Value;
		if (AnomalyInfo->ActorName == ActorName)
		{
			return AnomalyInfo;
		}
	}

	return AnomalyInfo;
}

FRespawnInfoBase* UHSWorldSubsystem::GetRespawnData(int32 ActorNum)
{
	return RespawnData->FindRow<FRespawnInfoBase>(*FString::FromInt(ActorNum), TEXT(""));
}

FLocalizationBase* UHSWorldSubsystem::GetLocalizationLocationData(FName Original)
{
	FLocalizationBase* LocalizationInfo = nullptr;

	for (auto RowData : LocalizationLocationData->GetRowMap())
	{
		LocalizationInfo = (FLocalizationBase*)RowData.Value;
		if (LocalizationInfo->Original == Original)
		{
			return LocalizationInfo;
		}
	}

	return LocalizationInfo;
}

FLocalizationBase* UHSWorldSubsystem::GetLocalizationAnomalyData(FName Original)
{
	FLocalizationBase* LocalizationInfo = nullptr;

	for (auto RowData : LocalizationAnomalyData->GetRowMap())
	{
		LocalizationInfo = (FLocalizationBase*)RowData.Value;
		if (LocalizationInfo->Original == Original)
		{
			return LocalizationInfo;
		}
	}

	return LocalizationInfo;
}

#pragma endregion

#pragma region Setting Anomaly

void UHSWorldSubsystem::FindAnomalyBPClass()
{
	if (!AnomalyData)
	{
		return;
	}

	for (int32 CurrentNum = 0; CurrentNum < AnomalyData->GetRowMap().Num(); CurrentNum++)
	{
		FString BPClassPath = GetAnomalyData(CurrentNum + 1)->Path;
		UClass* LoadClass = StaticLoadClass(AHSAnomalyBase::StaticClass(), nullptr, *BPClassPath);

		AnomalyClasses.AddUnique(LoadClass);
	}
}

void UHSWorldSubsystem::CreateAnomalyObjects(UWorld* CurrentWorld)
{
	if (!AnomalyData)
	{
		return;
	}

	for (int32 CurrentNum = 0; CurrentNum < AnomalyClasses.Num(); CurrentNum++)
	{
		FVector AnomalyLocation = FVector(GetAnomalyData(CurrentNum + 1)->LocationX, GetAnomalyData(CurrentNum + 1)->LocationY, GetAnomalyData(CurrentNum + 1)->LocationZ);
		FRotator AnomalyRotation = FRotator(GetAnomalyData(CurrentNum + 1)->RotationY, GetAnomalyData(CurrentNum + 1)->RotationZ, GetAnomalyData(CurrentNum + 1)->RotationX);

		AHSAnomalyBase* SpawnedAnomaly = CurrentWorld->SpawnActor<AHSAnomalyBase>(AnomalyClasses[CurrentNum], AnomalyLocation, AnomalyRotation);
		SpawnedAnomalys.AddUnique(SpawnedAnomaly);
		SpawnedAnomaly->LocationData = GetAnomalyData(CurrentNum + 1)->Place;
		SpawnedAnomaly->ObjectData = GetAnomalyData(CurrentNum + 1)->ActorName;
	}
}

void UHSWorldSubsystem::DeleteAnomalyObjects()
{
	for (auto DeleteActor : SpawnedAnomalys)
	{
		DeleteActor->Destroy();
		DeleteActor = nullptr;
	}

	AnomalyClasses.Empty();
	SpawnedAnomalys.Empty();
}

#pragma endregion

#pragma region Setting Monster

void UHSWorldSubsystem::FindMonsterBPClass()
{

}

void UHSWorldSubsystem::SpawnMapMonsters(UWorld* CurrentWorld)
{

}

void UHSWorldSubsystem::DeleteHotelMonsters()
{
	for (auto DeleteActor : SpawnedMonsters)
	{
		DeleteActor->Destroy();
		DeleteActor = nullptr;
	}

	SpawnedMonsters.Empty();
}

#pragma endregion

#pragma region Anomaly Event

void UHSWorldSubsystem::EndAnomalyEvent(AHSMonsterBase* Attacker)
{
	CurrentAnomaly = 0;
}

void UHSWorldSubsystem::AnomalyEventTimer()
{
	int32 RandomTime = FMath::RandRange(-20, 20);

	GetWorld()->GetTimerManager().SetTimer(AnomalyEventHandle, this, &ThisClass::StartRandomAnomalyEvent, AnmalyEventDuration + RandomTime, false);
}

void UHSWorldSubsystem::StartRandomAnomalyEvent()
{
	StartAnomalyEvent();

	CurrentAnomaly++;
	CheckAnomalyEvent();

	AnomalyEventOccur.Broadcast();

	AnomalyEventTimer();
}

void UHSWorldSubsystem::StartAnomalyEvent()
{
	int32 RandomObject = FMath::RandRange(0, SpawnedAnomalys.Num() - 1);

	if (!SpawnedAnomalys[RandomObject]->CanApplyAnomalyEvent())
	{
		StartAnomalyEvent();
		return;
	}

	SpawnedAnomalys[RandomObject]->StartRandomAnomaly(RandomObject);
}

void UHSWorldSubsystem::CheckAnomalyEvent()
{
	if (CurrentAnomaly < MaxAnomaly)
	{
		return;
	}

	AHSPlayer* HSPlayer = Cast<AHSPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	HSPlayer->PlayerDieDelegate.Broadcast(nullptr);
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
		AHSPlayer* HSPlayer = Cast<AHSPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		HSPlayer->PlayerDieDelegate.Broadcast(nullptr);
	}
}

#pragma endregion

#pragma region Wait

void UHSWorldSubsystem::WaitAnomalyTimer()
{
	GetWorld()->GetTimerManager().SetTimer(WaitAnomalyEventHandle, this, &ThisClass::AnomalyEventTimer, WaitAnomalyTime, false);
}

#pragma endregion