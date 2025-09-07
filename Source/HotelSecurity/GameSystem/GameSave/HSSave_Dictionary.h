// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AI/Character/Monster_Base.h"
#include "HSSave_Dictionary.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSSave_Dictionary : public USaveGame
{
	GENERATED_BODY()

public:
	bool LoadDictionaryData(EMonsterType MonsterName);
	void SaveDictionaryData(EMonsterType MonsterName);

protected:
	UPROPERTY(SaveGame)
	bool bFindBellyMan = false;
	
	UPROPERTY(SaveGame)
	bool bFindHotelManager = false;

	UPROPERTY(SaveGame)
	bool bFindBlackVeil = false;

	UPROPERTY(SaveGame)
	bool bFindMiner = false;

	UPROPERTY(SaveGame)
	bool bFindHangingBody = false;

	UPROPERTY(SaveGame)
	bool bFindNurse = false;

	UPROPERTY(SaveGame)
	bool bFindMelodia = false;

	UPROPERTY(SaveGame)
	bool bFindPlagueDoctor = false;

	UPROPERTY(SaveGame)
	bool bFindDeadWave = false;

	UPROPERTY(SaveGame)
	bool bFindEclipser = false;

	UPROPERTY(SaveGame)
	bool bFindTimeEater = false;
};