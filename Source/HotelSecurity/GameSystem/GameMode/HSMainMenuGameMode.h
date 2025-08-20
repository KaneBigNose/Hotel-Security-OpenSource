// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HSMainMenuGameMode.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion
	
#pragma region Widget

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_Base> MainMenuClass;

#pragma endregion

};