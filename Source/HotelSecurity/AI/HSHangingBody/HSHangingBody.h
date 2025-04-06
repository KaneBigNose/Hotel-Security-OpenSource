// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/HSMonsterBase/HSMonsterBase.h"
#include "HSHangingBody.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSHangingBody : public AHSMonsterBase
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AHSHangingBody();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BellyManWalkSpeed = 180.f;

#pragma endregion

#pragma region Overlap Event

public:
	UFUNCTION()
	void FearSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* FearSphere;

	bool bIsOverlapped = false;

#pragma endregion

#pragma region Fear

public:
	bool GetIsFearing() { return bFear; }

protected:
	FTimerHandle DisappearHandle;

	void Fearing(class AHSPlayer* HSPlayer);
	void DisappearHangingBody();

	float DisappearDuration = 3.5f;

	bool bFear = false;

#pragma endregion

#pragma region Sound

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class UAudioComponent* HangingBodyAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundWave* BaseSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundWave* FearSound;

	void PlayHangingBodySound(class USoundWave* TargetSound);

#pragma endregion

};