// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameSystem/GameInstance/HSGameInstance.h"
#include "HSSave_Clear.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSSave_Clear : public USaveGame
{
	GENERATED_BODY()

public:
	void LoadClearData(int32& ClearCount, bool& bHotel, bool& bMine, bool& bHospital);
	void SaveClearData(EMapType CurrentMap);
	
protected:
	UPROPERTY(SaveGame)
	int32 MapClearCount = 0;

	UPROPERTY(SaveGame)
	bool bIsClearHotel;

	UPROPERTY(SaveGame)
	bool bIsClearMine;

	UPROPERTY(SaveGame)
	bool bIsClearHospital;
};