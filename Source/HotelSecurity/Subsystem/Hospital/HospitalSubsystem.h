// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Subsystem/HSWorldSubsystem.h"
#include "HospitalSubsystem.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHospitalSubsystem : public UHSWorldSubsystem
{
	GENERATED_BODY()

#pragma region Base

public:
	UHospitalSubsystem();

protected:
	virtual void Deinitialize() override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

#pragma endregion

#pragma region Setting Monster

protected:
	virtual void FindMonsterBPClass() override;
	virtual void SpawnMapMonsters(UWorld* CurrentWorld) override;

	FTimerHandle SpawnNextMonsterHandle;

	float NextMonsterTime = 600.f;

	void SpawnNurses();
	void SpawnPlagueDoctors();
	void SpawnMelodia();

	FVector MonsterLocation1;
	FRotator MonsterRotation1;

	FVector MonsterLocation2;
	FRotator MonsterRotation2;

	FVector MonsterLocation3;
	FRotator MonsterRotation3;

	FVector MonsterLocation4;
	FRotator MonsterRotation4;

	FVector MonsterLocation5;
	FRotator MonsterRotation5;

protected:
	UPROPERTY()
	TSubclassOf<class AHSNurse> Nurse1Class;

	UPROPERTY()
	TSubclassOf<class AHSNurse> Nurse2Class;

	UPROPERTY()
	TSubclassOf<class AHSPlagueDoctor> PlagueDoctorClass1;

	UPROPERTY()
	TSubclassOf<class AHSPlagueDoctor> PlagueDoctorClass2;

	UPROPERTY()
	TSubclassOf<class AHSMelodia> MelodiaClass;

#pragma endregion

};