// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/HSMonsterBase/HSMonsterBase.h"
#include "HSMelodia.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSMelodia : public AHSMonsterBase
{
	GENERATED_BODY()

#pragma region Base

public:
	AHSMelodia();

protected:
	virtual void Tick(float DeltaTime) override;

#pragma endregion

#pragma region Overlap Event

public:
	UFUNCTION()
	void OnMelodySphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnMelodySphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* MelodySphere;

#pragma endregion

#pragma region Calculate

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MelodiaWalkSpeed = 40.f;

#pragma endregion

#pragma region Sound

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class UAudioComponent* MelodiaAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundWave* BaseSound;

	void PlayBaseSound();

#pragma endregion

#pragma region Fear

protected:
	FTimerHandle FearHandle;

	void IncreaseFear();

#pragma endregion

};