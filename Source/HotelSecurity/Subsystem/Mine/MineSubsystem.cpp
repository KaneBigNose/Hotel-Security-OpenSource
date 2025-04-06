// Made by LSH

#include "Subsystem/Mine/MineSubsystem.h"
#include "AI/HSBlackVeil/HSBlackVeil.h"
#include "AI/HSMiner/HSMiner.h"
#include "AI/HSHangingBody/HSHangingBody.h"
#include "AI/Data/Mine/MineRespawnInfo.h"

#pragma region Base

UMineSubsystem::UMineSubsystem()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> AnomalyDataFinder(TEXT("/Game/HotelSecurity/Data/Mine/DT_AnomalyInfo"));
	if (AnomalyDataFinder.Succeeded())
	{
		AnomalyData = AnomalyDataFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> RespawnDataFinder(TEXT("/Game/HotelSecurity/AI/Data/Mine/DT_MineRespawnInfo"));
	if (RespawnDataFinder.Succeeded())
	{
		RespawnData = RespawnDataFinder.Object;
	}

	FindAnomalyBPClass();
	FindMonsterBPClass();
}

void UMineSubsystem::Deinitialize()
{
	Super::Deinitialize();

	DeleteAnomalyObjects();
	DeleteHotelMonsters();
}

void UMineSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	FString MapName = FPaths::GetCleanFilename(GetWorld()->GetMapName());
	if (!MapName.EndsWith(TEXT("Mine")))
	{
		return;
	}

	CreateAnomalyObjects(GetWorld());

	SpawnMapMonsters(GetWorld());

	WaitAnomalyTimer();

	GetWorld()->GetTimerManager().SetTimer(HangingBodyHandle, this, &ThisClass::SpawnHangingBody, 150.f, true);
}

#pragma endregion

#pragma region Setting Monster

void UMineSubsystem::FindMonsterBPClass()
{
	FString BPClassPath1 = GetRespawnData(1)->Path;
	Miner1Class = StaticLoadClass(AHSMiner::StaticClass(), nullptr, *BPClassPath1);

	FString BPClassPath2 = GetRespawnData(2)->Path;
	Miner2Class = StaticLoadClass(AHSMiner::StaticClass(), nullptr, *BPClassPath2);

	FString BPClassPath3 = GetRespawnData(3)->Path;
	HangingBodyClass = StaticLoadClass(AHSHangingBody::StaticClass(), nullptr, *BPClassPath3);

	FString BPClassPath4 = GetRespawnData(4)->Path;
	BlackVeilClass = StaticLoadClass(AHSBlackVeil::StaticClass(), nullptr, *BPClassPath4);
}

void UMineSubsystem::SpawnMapMonsters(UWorld* CurrentWorld)
{
	MonsterLocation1 = FVector(GetRespawnData(1)->LocationX, GetRespawnData(1)->LocationY, GetRespawnData(1)->LocationZ);
	MonsterRotation1 = FRotator(GetRespawnData(1)->RotationY, GetRespawnData(1)->RotationZ, GetRespawnData(1)->RotationX);

	MonsterLocation2 = FVector(GetRespawnData(2)->LocationX, GetRespawnData(2)->LocationY, GetRespawnData(2)->LocationZ);
	MonsterRotation2 = FRotator(GetRespawnData(2)->RotationY, GetRespawnData(2)->RotationZ, GetRespawnData(2)->RotationX);

	MonsterLocation3 = FVector(GetRespawnData(3)->LocationX, GetRespawnData(3)->LocationY, GetRespawnData(3)->LocationZ);
	MonsterRotation3 = FRotator(GetRespawnData(3)->RotationY, GetRespawnData(3)->RotationZ, GetRespawnData(3)->RotationX);

	MonsterLocation4 = FVector(GetRespawnData(4)->LocationX, GetRespawnData(4)->LocationY, GetRespawnData(4)->LocationZ);
	MonsterRotation4 = FRotator(GetRespawnData(4)->RotationY, GetRespawnData(4)->RotationZ, GetRespawnData(4)->RotationX);

	FTimerHandle MinersHandle;

	GetWorld()->GetTimerManager().SetTimer(MinersHandle, this, &ThisClass::SpawnMiners, 250.f, false);
}

void UMineSubsystem::SpawnBlackVeil()
{
	SpawnedMonsters.AddUnique(Cast<AHSMonsterBase>(GetWorld()->SpawnActor<AHSBlackVeil>(BlackVeilClass, MonsterLocation4, MonsterRotation4)));
}

void UMineSubsystem::SpawnMiners()
{
	SpawnedMonsters.AddUnique(Cast<AHSMonsterBase>(GetWorld()->SpawnActor<AHSMiner>(Miner1Class, MonsterLocation1, MonsterRotation1)));
	SpawnedMonsters.AddUnique(Cast<AHSMonsterBase>(GetWorld()->SpawnActor<AHSMiner>(Miner2Class, MonsterLocation2, MonsterRotation2)));

	GetWorld()->GetTimerManager().SetTimer(SpawnNextMonsterHandle, this, &ThisClass::SpawnBlackVeil, NextMonsterTime, false);
}

void UMineSubsystem::SpawnHangingBody()
{
	GetWorld()->SpawnActor<AHSHangingBody>(HangingBodyClass, MonsterLocation3, MonsterRotation3);
}

#pragma endregion