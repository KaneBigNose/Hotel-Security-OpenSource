// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Subsystem/HSWorldSubsystem.h"
#include "MineSubsystem.generated.h"

UCLASS()
class HOTEL_SECURITY_API UMineSubsystem : public UHSWorldSubsystem
{
	GENERATED_BODY()

#pragma region Base

public:
	UMineSubsystem();

protected:
	virtual void Deinitialize() override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

#pragma endregion

#pragma region Setting Monster

protected:
	virtual void FindMonsterBPClass() override;
	virtual void SpawnMapMonsters(UWorld* CurrentWorld) override;

	FTimerHandle SpawnNextMonsterHandle;
	FTimerHandle HangingBodyHandle;

	float NextMonsterTime = 1500.f;

	void SpawnBlackVeil();
	void SpawnMiners();
	void SpawnHangingBody();

	FVector MonsterLocation1;
	FRotator MonsterRotation1;

	FVector MonsterLocation2;
	FRotator MonsterRotation2;

	FVector MonsterLocation3;
	FRotator MonsterRotation3;

	FVector MonsterLocation4;
	FRotator MonsterRotation4;

protected:
	UPROPERTY()
	TSubclassOf<class AHSBlackVeil> BlackVeilClass;

	UPROPERTY()
	TSubclassOf<class AHSMiner> Miner1Class;

	UPROPERTY()
	TSubclassOf<class AHSMiner> Miner2Class;

	UPROPERTY()
	TSubclassOf<class AHSHangingBody> HangingBodyClass;

#pragma endregion

};