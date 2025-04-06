// Made by LSH

#include "Subsystem/Hotel/HotelSubsystem.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "AI/HSBellyMan/HSBellyMan.h"
#include "AI/HSBlackVeil/HSBlackVeil.h"
#include "AI/HSHotelManager/HSHotelManager.h"
#include "AI/Data/Hotel/HotelRespawnInfo.h"

#pragma region Base

UHotelSubsystem::UHotelSubsystem()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> AnomalyDataFinder(TEXT("/Game/HotelSecurity/Data/Hotel/DT_AnomalyInfo"));
	if (AnomalyDataFinder.Succeeded())
	{
		AnomalyData = AnomalyDataFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> HotelRespawnDataFinder(TEXT("/Game/HotelSecurity/AI/Data/Hotel/DT_HotelRespawnInfo"));
	if (HotelRespawnDataFinder.Succeeded())
	{
		RespawnData = HotelRespawnDataFinder.Object;
	}

	FindAnomalyBPClass();
	FindMonsterBPClass();
}

void UHotelSubsystem::Deinitialize()
{
	Super::Deinitialize();

	DeleteAnomalyObjects();
	DeleteHotelMonsters();
}

void UHotelSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	FString MapName = FPaths::GetCleanFilename(GetWorld()->GetMapName());
	if (!MapName.EndsWith(TEXT("Hotel")))
	{
		return;
	}

	CreateAnomalyObjects(GetWorld());

	SpawnMapMonsters(GetWorld());

	WaitAnomalyTimer();
}

#pragma endregion

#pragma region Setting Monster

void UHotelSubsystem::FindMonsterBPClass()
{
	FString BPClassPath1 = GetRespawnData(1)->Path;
	BellyManClass = StaticLoadClass(AHSBellyMan::StaticClass(), nullptr, *BPClassPath1);

	FString BPClassPath2 = GetRespawnData(2)->Path;
	BlackVeilClass = StaticLoadClass(AHSBlackVeil::StaticClass(), nullptr, *BPClassPath2);

	FString BPClassPath3 = GetRespawnData(3)->Path;
	HotelManagerClass = StaticLoadClass(AHSHotelManager::StaticClass(), nullptr, *BPClassPath3);
}

void UHotelSubsystem::SpawnMapMonsters(UWorld* HotelWorld)
{
	MonsterLocation1 = FVector(GetRespawnData(1)->LocationX, GetRespawnData(1)->LocationY, GetRespawnData(1)->LocationZ);
	MonsterRotation1 = FRotator(GetRespawnData(1)->RotationY, GetRespawnData(1)->RotationZ, GetRespawnData(1)->RotationX);

	MonsterLocation2 = FVector(GetRespawnData(2)->LocationX, GetRespawnData(2)->LocationY, GetRespawnData(2)->LocationZ);
	MonsterRotation2 = FRotator(GetRespawnData(2)->RotationY, GetRespawnData(2)->RotationZ, GetRespawnData(2)->RotationX);

	MonsterLocation3 = FVector(GetRespawnData(3)->LocationX, GetRespawnData(3)->LocationY, GetRespawnData(3)->LocationZ);
	MonsterRotation3 = FRotator(GetRespawnData(3)->RotationY, GetRespawnData(3)->RotationZ, GetRespawnData(3)->RotationX);

	SpawnedMonsters.AddUnique(Cast<AHSMonsterBase>(GetWorld()->SpawnActor<AHSHotelManager>(HotelManagerClass, MonsterLocation3, MonsterRotation3)));

	GetWorld()->GetTimerManager().SetTimer(SpawnNextMonsterHandle, this, &ThisClass::SpawnHotelManager, NextMonsterTime, false);
}

void UHotelSubsystem::SpawnBellyMan()
{
	SpawnedMonsters.AddUnique(Cast<AHSMonsterBase>(GetWorld()->SpawnActor<AHSBellyMan>(BellyManClass, MonsterLocation1, MonsterRotation1)));
}

void UHotelSubsystem::SpawnBlackVeil()
{
	SpawnedMonsters.AddUnique(Cast<AHSMonsterBase>(GetWorld()->SpawnActor<AHSBlackVeil>(BlackVeilClass, MonsterLocation2, MonsterRotation2)));

	GetWorld()->GetTimerManager().SetTimer(SpawnNextMonsterHandle, this, &ThisClass::SpawnBellyMan, NextMonsterTime, false);
}

void UHotelSubsystem::SpawnHotelManager()
{
	SpawnedMonsters.AddUnique(Cast<AHSMonsterBase>(GetWorld()->SpawnActor<AHSHotelManager>(HotelManagerClass, MonsterLocation3, MonsterRotation3)));

	GetWorld()->GetTimerManager().SetTimer(SpawnNextMonsterHandle, this, &ThisClass::SpawnBlackVeil, NextMonsterTime, false);
}

#pragma endregion