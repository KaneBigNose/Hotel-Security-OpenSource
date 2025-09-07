// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "HSAudioController.generated.h"

#pragma region Declare

UENUM(BlueprintType)
enum class EBGMType : uint8
{
	MainMenu		UMETA(DisplayName = "MainMenu"),
	Normal			UMETA(DisplayName = "Normal"),
	Chased			UMETA(DisplayName = "Chased"),
	HeartBeat		UMETA(DisplayName = "HeartBeat"),
	GameClear		UMETA(DisplayName = "GameClear"),
	GameOver		UMETA(DisplayName = "GameOver"),
	ReportResult	UMETA(DisplayName = "ReportResult"),
	TimeStopStart	UMETA(DisplayName = "TimeStopStart"),
	TimeStop		UMETA(DisplayName = "TimeStop"),
	TimeStopEnd		UMETA(DisplayName = "TimeStopEnd")
};

UENUM(BlueprintType)
enum class EAnomalySoundType : uint8
{
	Occurrence	UMETA(DisplayName = "Occurrence"),
	Warning		UMETA(DisplayName = "Warning")
};

#pragma endregion

UCLASS()
class HOTEL_SECURITY_API UHSAudioController : public UWorldSubsystem
{
	GENERATED_BODY()

#pragma region Base

public:
	UHSAudioController();

protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

public:
	void AudioSetting();

protected:
	UPROPERTY()
	TObjectPtr<class AHSPlayer> HSPlayer;

	UPROPERTY()
	TObjectPtr<class UHSAbilitySystemComponent> ASC;

#pragma endregion

#pragma region Data

protected:
	struct FAudioInfo* GetSoundData(int32 RowNum);
	struct FAudioInfo* GetSoundData(FName TargetName);

	void FindSounds();

protected:
	UDataTable* AudioDataTable;

#pragma endregion

#pragma region BGM

protected:
	UFUNCTION()
	void PlayBGM();

	UFUNCTION()
	void TagChangeEvent_Chased(FGameplayTag ChangeTag, int32 NewCount);

	UFUNCTION()
	void TagChangeEvent_HeartBeat(FGameplayTag ChangeTag, int32 NewCount);

	UFUNCTION()
	void GameClearFunc();

	UFUNCTION()
	void TagChangeEvent_GameOver(FGameplayTag ChangeTag, int32 NewCount);

	UFUNCTION()
	void TagChangeEvent_Report(FGameplayTag ChangeTag, int32 NewCount);

	UFUNCTION()
	void TimeStopFunc(bool bIsStop);

protected:
	EBGMType SelectedBGM;

	bool bIsTimeStop = false;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> BGM_AudioComponent;

	UPROPERTY()
	TMap<FName, TObjectPtr<class USoundWave>> BGM_Map;

protected:
	UFUNCTION()
	void OnHeartBeatRangeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHeartBeatRangeEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY()
	TObjectPtr<class USphereComponent> HeartBeatRange;

#pragma endregion

#pragma region Anomaly

protected:
	UFUNCTION()
	void PlayAnomalyOccurSound(int32 CurrentAnomaly, const int32 MaxAnomaly);

protected:
	EAnomalySoundType SelectedAnomalySound;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> Anomaly_AudioComponent;

	UPROPERTY()
	TMap<FName, TObjectPtr<class USoundWave>> Anomaly_Map;

#pragma endregion

};