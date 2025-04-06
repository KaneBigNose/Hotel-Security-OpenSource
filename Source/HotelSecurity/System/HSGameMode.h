// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HSGameMode.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSGameMode : public AGameModeBase
{
	GENERATED_BODY()

#pragma region Base

public:
	AHSGameMode();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	class UHSGameInstance* GameInstance;

#pragma endregion

#pragma region Loading

protected:
	FTimerHandle LoadingHandle;

	void StartGameplay();

#pragma endregion

#pragma region Widget

public:
	void SettingMainMenu();
	void SettingInGame();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UHSMainMenu> MainMenuClass;

	UPROPERTY()
	UHSMainMenu* MainMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UHSInGameBase> InGameBaseClass;

	UPROPERTY()
	UHSInGameBase* InGameBaseWidget;

#pragma endregion

#pragma region Timer

public:
	int32 GetCurrentHour();
	int32 GetCurrentMinute();

protected:
	FTimerHandle PlayTimeHandle;

	int32 CurrentPlayTime = 0;
	int32 EndPlayTime = 480;

	float InGameOneMinute = 4.5f;

	void PlayTimeTimer();
	void IncreasePlayTime();

	UFUNCTION()
	void PlayTimeStopTimer();

#pragma endregion

};