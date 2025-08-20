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

public:
	UHSPlayerVision();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	TObjectPtr<class AHSPlayer> HSPlayer;

	UPROPERTY()
	TObjectPtr<class AHSPlayerController> PC;

#pragma endregion

#pragma region Vision

protected:
	void CheckPlayerVision();

	float VisionDuration = 0.3f;

#pragma endregion

};