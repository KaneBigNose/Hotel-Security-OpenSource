// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HSMainMenuGameMode.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UHSMainMenu> MainMenuClass;

	UPROPERTY()
	class UHSMainMenu* MainMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundWave* MainMenuBGM;
};