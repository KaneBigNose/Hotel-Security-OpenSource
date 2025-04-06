// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HSGameSave.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSGameSave : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	bool bIsClearHotel = false;

	UPROPERTY()
	bool bIsClearMine = false;

	UPROPERTY()
	bool bIsClearHospital = false;
};