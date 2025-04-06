// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HSPlayerVision.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOTEL_SECURITY_API UHSPlayerVision : public UActorComponent
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	class AHSPlayer* HSPlayer;

	UPROPERTY()
	class AHSPlayerController* HSPlayerController;

#pragma endregion

#pragma region Vision

protected:
	FTimerHandle VisionHandle;

	float VisionDuration = 0.3f;

	void CheckPlayerVision();

#pragma endregion

};