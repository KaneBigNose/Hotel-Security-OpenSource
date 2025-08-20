// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HSSave_Tutorial.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSSave_Tutorial : public USaveGame
{
	GENERATED_BODY()
	
public:
	void LoadTutorialData(bool& bFirst);
	void SaveTutorialData(bool bFirst);

protected:
	UPROPERTY(SaveGame)
	bool bIsFirstPlay = true;
};