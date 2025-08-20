// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Delegates/DelegateCombinations.h"
#include "HSGameMode.generated.h"

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FPlayTime, int32, Hour, int32, Minute, FString, Center);

#pragma endregion

UCLASS()
class HOTEL_SECURITY_API AHSGameMode : public AGameModeBase
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_Base> InGameClass;

#pragma endregion

#pragma region Timer

public:
	FPlayTime PlayTime;

	int32 GetCurrentHour();
	int32 GetCurrentMinute();

protected:
	FTimerHandle PlayTimeHandle;

	void IncreasePlayTime();

protected:
	int32 InGameOneMinute = 8; // real time 4 second

	int32 CurrentPlayTime = 0;
	int32 EndPlayTime = 480 * InGameOneMinute;

	bool bOnCenter = true;

#pragma endregion

};