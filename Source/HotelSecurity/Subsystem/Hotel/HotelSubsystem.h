// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Subsystem/HSWorldSubsystem.h"
#include "HotelSubsystem.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHotelSubsystem : public UHSWorldSubsystem
{
	GENERATED_BODY()
	
#pragma region Base

public:
	UHotelSubsystem();

protected:
	virtual void Deinitialize() override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

#pragma endregion

#pragma region Setting Monster

protected:
	virtual void FindMonsterBPClass() override;
	virtual void SpawnMapMonsters(UWorld* HotelWorld) override;

	FTimerHandle SpawnNextMonsterHandle;
	float NextMonsterTime = 300.f;

	void SpawnBellyMan();
	void SpawnBlackVeil();
	void SpawnHotelManager();

	FVector MonsterLocation1;
	FRotator MonsterRotation1;

	FVector MonsterLocation2;
	FRotator MonsterRotation2;

	FVector MonsterLocation3;
	FRotator MonsterRotation3;

protected:
	UPROPERTY()
	TSubclassOf<class AHSBellyMan> BellyManClass;

	UPROPERTY()
	TSubclassOf<class AHSBlackVeil> BlackVeilClass;

	UPROPERTY()
	TSubclassOf<class AHSHotelManager> HotelManagerClass;

#pragma endregion

};