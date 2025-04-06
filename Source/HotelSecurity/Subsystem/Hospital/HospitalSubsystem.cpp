// Made by LSH

#include "Subsystem/Hospital/HospitalSubsystem.h"
#include "AI/HSNurse/HSNurse.h"
#include "AI/HSPlagueDoctor/HSPlagueDoctor.h"
#include "AI/HSMelodia/HSMelodia.h"
#include "AI/Data/Hospital/HospitalRespawnInfo.h"
#include "Anomaly/Data/Hospital/HospitalAnomalyInfo.h"

#pragma region Base

UHospitalSubsystem::UHospitalSubsystem()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> AnomalyDataFinder(TEXT("/Game/HotelSecurity/Data/Hospital/DT_AnomalyInfo"));
	if (AnomalyDataFinder.Succeeded())
	{
		AnomalyData = AnomalyDataFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> RespawnDataFinder(TEXT("/Game/HotelSecurity/AI/Data/Hospital/DT_HospitalRespawnInfo"));
	if (RespawnDataFinder.Succeeded())
	{
		RespawnData = RespawnDataFinder.Object;
	}

	FindAnomalyBPClass();
	FindMonsterBPClass();
}

void UHospitalSubsystem::Deinitialize()
{
	Super::Deinitialize();

	DeleteAnomalyObjects();
	DeleteHotelMonsters();
}

void UHospitalSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	FString MapName = FPaths::GetCleanFilename(GetWorld()->GetMapName());
	if (!MapName.EndsWith(TEXT("Hospital")))
	{
		return;
	}

	CreateAnomalyObjects(GetWorld());

	SpawnMapMonsters(GetWorld());

	WaitAnomalyTimer();
}

#pragma endregion

#pragma region Setting Monster

void UHospitalSubsystem::FindMonsterBPClass()
{
	FString BPClassPath1 = GetRespawnData(1)->Path;
	Nurse1Class = StaticLoadClass(AHSNurse::StaticClass(), nullptr, *BPClassPath1);

	FString BPClassPath2 = GetRespawnData(2)->Path;
	Nurse2Class = StaticLoadClass(AHSNurse::StaticClass(), nullptr, *BPClassPath2);

	FString BPClassPath3 = GetRespawnData(3)->Path;
	PlagueDoctorClass1 = StaticLoadClass(AHSPlagueDoctor::StaticClass(), nullptr, *BPClassPath3);

	FString BPClassPath4 = GetRespawnData(4)->Path;
	MelodiaClass = StaticLoadClass(AHSMelodia::StaticClass(), nullptr, *BPClassPath4);

	FString BPClassPath5 = GetRespawnData(5)->Path;
	PlagueDoctorClass2 = StaticLoadClass(AHSPlagueDoctor::StaticClass(), nullptr, *BPClassPath5);
}

void UHospitalSubsystem::SpawnMapMonsters(UWorld* CurrentWorld)
{
	MonsterLocation1 = FVector(GetRespawnData(1)->LocationX, GetRespawnData(1)->LocationY, GetRespawnData(1)->LocationZ);
	MonsterRotation1 = FRotator(GetRespawnData(1)->RotationY, GetRespawnData(1)->RotationZ, GetRespawnData(1)->RotationX);

	MonsterLocation2 = FVector(GetRespawnData(2)->LocationX, GetRespawnData(2)->LocationY, GetRespawnData(2)->LocationZ);
	MonsterRotation2 = FRotator(GetRespawnData(2)->RotationY, GetRespawnData(2)->RotationZ, GetRespawnData(2)->RotationX);

	MonsterLocation3 = FVector(GetRespawnData(3)->LocationX, GetRespawnData(3)->LocationY, GetRespawnData(3)->LocationZ);
	MonsterRotation3 = FRotator(GetRespawnData(3)->RotationY, GetRespawnData(3)->RotationZ, GetRespawnData(3)->RotationX);

	MonsterLocation4 = FVector(GetRespawnData(4)->LocationX, GetRespawnData(4)->LocationY, GetRespawnData(4)->LocationZ);
	MonsterRotation4 = FRotator(GetRespawnData(4)->RotationY, GetRespawnData(4)->RotationZ, GetRespawnData(4)->RotationX);

	MonsterLocation5 = FVector(GetRespawnData(5)->LocationX, GetRespawnData(5)->LocationY, GetRespawnData(5)->LocationZ);
	MonsterRotation5 = FRotator(GetRespawnData(5)->RotationY, GetRespawnData(5)->RotationZ, GetRespawnData(5)->RotationX);

	SpawnNurses();
}

void UHospitalSubsystem::SpawnNurses()
{
	SpawnedMonsters.AddUnique(Cast<AHSMonsterBase>(GetWorld()->SpawnActor<AHSNurse>(Nurse1Class, MonsterLocation1, MonsterRotation1)));
	SpawnedMonsters.AddUnique(Cast<AHSMonsterBase>(GetWorld()->SpawnActor<AHSNurse>(Nurse2Class, MonsterLocation2, MonsterRotation2)));

	GetWorld()->GetTimerManager().SetTimer(SpawnNextMonsterHandle, this, &ThisClass::SpawnPlagueDoctors, NextMonsterTime, false);
}

void UHospitalSubsystem::SpawnPlagueDoctors()
{
	SpawnedMonsters.AddUnique(Cast<AHSMonsterBase>(GetWorld()->SpawnActor<AHSPlagueDoctor>(PlagueDoctorClass1, MonsterLocation3, MonsterRotation3)));
	SpawnedMonsters.AddUnique(Cast<AHSMonsterBase>(GetWorld()->SpawnActor<AHSPlagueDoctor>(PlagueDoctorClass2, MonsterLocation5, MonsterRotation5)));

	GetWorld()->GetTimerManager().SetTimer(SpawnNextMonsterHandle, this, &ThisClass::SpawnMelodia, NextMonsterTime, false);
}

void UHospitalSubsystem::SpawnMelodia()
{
	SpawnedMonsters.AddUnique(Cast<AHSMonsterBase>(GetWorld()->SpawnActor<AHSMelodia>(MelodiaClass, MonsterLocation4, MonsterRotation4)));
}

#pragma endregion