// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "HSPlayerSound.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOTEL_SECURITY_API UHSPlayerSound : public UActorComponent
{
	GENERATED_BODY()

#pragma region Base

public:
	UHSPlayerSound();

protected:
	virtual void BeginPlay() override;

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
	class AHSPlayer* HSPlayer;

	UPROPERTY()
	class UHSWorldSubsystem* MapSubsystem;

#pragma endregion

#pragma region Anomaly

public:
	UFUNCTION()
	void PlayAnomalyEventSound();
	void StopAnomalyEventSound();
	void PlayAnomalyFixSound();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|Anomaly")
	class UAudioComponent* AnomalyEventAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|Anomaly")
	class USoundWave* AnomalyOccurenceSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|Anomaly")
	class USoundWave* AnomalyWarningSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|Anomaly")
	class USoundWave* AnomalyFixingSound;

#pragma endregion

#pragma region Effect

public:
	void PlayEffectSound(bool bIsChased, bool bStopDelayed, float DelayDuration = 0.f);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|Effect")
	class UAudioComponent* EffectAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|Effect")
	class USoundWave* DeathEffectSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|Effect")
	class USoundWave* ChasedEffectSound;

#pragma endregion

#pragma region BGM

public:
	void PlayBGM(bool bStop);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|BGM")
	class UAudioComponent* BGMAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|BGM")
	class USoundWave* NormalBGM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|BGM")
	class USoundWave* ChasedBGM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|BGM")
	class USoundWave* ClearBGM;

public:
	void SetBGMNormal() { BGMAudioComponent->Sound = NormalBGM; }
	void SetBGMChased() { BGMAudioComponent->Sound = ChasedBGM; }
	void SetBGMClear() { BGMAudioComponent->Sound = ClearBGM; }

#pragma endregion

#pragma region HeartBeat

protected:
	void PlayHeartBeatSound(bool bPlaySound);

	UFUNCTION()
	void OnHeartBeatRangeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHeartBeatRangeEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|HeartBeat")
	class UAudioComponent* HeartBeatAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|HeartBeat")
	class USoundWave* HeartBeatSound;

#pragma endregion

#pragma region Flash

public:
	void PlayFlashEquipSound(bool bStop);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|Flash")
	class UAudioComponent* FlashAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|Flash")
	class USoundWave* FlashEquipSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|Flash")
	float FlashNoisePower = 0.3f;

#pragma endregion

};