// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameSystem/GameInstance/HSGameInstance.h"
#include "HSSave_Tutorial.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSSave_Tutorial : public USaveGame
{
	GENERATED_BODY()
	
public:
	bool LoadTutorialData(EMapType SelectedMap = UHSGameInstance::SelectedMap);
	void SaveTutorialData(EMapType SelectedMap = UHSGameInstance::SelectedMap);

protected:
	UPROPERTY(SaveGame)
	bool bIsHotelFirst = true;

	UPROPERTY(SaveGame)
	bool bIsMineFirst = true;

	UPROPERTY(SaveGame)
	bool bIsHospitalFirst = true;
};