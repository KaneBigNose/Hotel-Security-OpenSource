// Made by LSH

#include "GameSystem/AudioController/HSAudioController.h"
#include "GameSystem/GameInstance/HSGameInstance.h"
#include "GameSystem/Subsystem/HSWorldSubsystem.h"
#include "GameSystem/Enum/HSEnumManager.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "AI/Character/Monster_Base.h"
#include "Data/Audio/AudioInfo.h"
#include "Player/Character/HSPlayer.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

UHSAudioController::UHSAudioController()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataFinder(TEXT("/Game/HotelSecurity/Data/Audio/DT_AudioInfo.DT_AudioInfo"));
	if (DataFinder.Succeeded())
	{
		AudioDataTable = DataFinder.Object;
	}

	FindSounds();
}

void UHSAudioController::OnWorldBeginPlay(UWorld& InWorld)
{
	if (UHSGameInstance::SelectedMap != EMapType::MainMenu)
	{
		return;
	}

	UHSGameInstance* GameInstance = GetWorld()->GetGameInstance<UHSGameInstance>();
	GameInstance->StageClear.RemoveDynamic(this, &ThisClass::GameClearFunc);
	GameInstance->StageClear.AddDynamic(this, &ThisClass::GameClearFunc);

	if (!BGM_AudioComponent)
	{
		BGM_AudioComponent = NewObject<UAudioComponent>();
		BGM_AudioComponent->RegisterComponentWithWorld(GetWorld());
		BGM_AudioComponent->AttachToComponent(GetWorld()->GetWorldSettings()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		BGM_AudioComponent->SetUISound(true);
		BGM_AudioComponent->OnAudioFinished.AddDynamic(this, &ThisClass::PlayBGM);
	}

	SelectedBGM = EBGMType::MainMenu;
	PlayBGM();
}

void UHSAudioController::AudioSetting()
{
	if (!BGM_AudioComponent)
	{
		BGM_AudioComponent = NewObject<UAudioComponent>();
		BGM_AudioComponent->RegisterComponentWithWorld(GetWorld());
		BGM_AudioComponent->AttachToComponent(GetWorld()->GetWorldSettings()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		BGM_AudioComponent->SetUISound(true);
		BGM_AudioComponent->OnAudioFinished.AddDynamic(this, &ThisClass::PlayBGM);
	}

	UHSGameInstance* GameInstance = GetWorld()->GetGameInstance<UHSGameInstance>();
	GameInstance->StageClear.RemoveDynamic(this, &ThisClass::GameClearFunc);
	GameInstance->StageClear.AddDynamic(this, &ThisClass::GameClearFunc);

	UHSWorldSubsystem* Subsystem = GetWorld()->GetSubsystem<UHSWorldSubsystem>();
	Subsystem->AnomalyEventOccur.RemoveDynamic(this, &ThisClass::PlayAnomalyOccurSound);
	Subsystem->AnomalyEventOccur.AddDynamic(this, &ThisClass::PlayAnomalyOccurSound);

	if (!Anomaly_AudioComponent)
	{
		Anomaly_AudioComponent = NewObject<UAudioComponent>();
		Anomaly_AudioComponent->RegisterComponentWithWorld(GetWorld());
		Anomaly_AudioComponent->AttachToComponent(GetWorld()->GetWorldSettings()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		Anomaly_AudioComponent->SetUISound(true);
	}

	if (!HSPlayer || !ASC)
	{
		HSPlayer = Cast<AHSPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		ASC = Cast<UHSAbilitySystemComponent>(HSPlayer->GetAbilitySystemComponent());

		ASC->RegisterGameplayTagEvent(HSGameplayTags::State::Chased, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::TagChangeEvent_Chased);
		ASC->RegisterGameplayTagEvent(HSGameplayTags::State::HeartBeat, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::TagChangeEvent_HeartBeat);
		ASC->RegisterGameplayTagEvent(HSGameplayTags::UI::PopUp::GameOver, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::TagChangeEvent_GameOver);
		ASC->RegisterGameplayTagEvent(HSGameplayTags::UI::PopUp::Report, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::TagChangeEvent_Report);
	}

	if (!HeartBeatRange)
	{
		HeartBeatRange = NewObject<USphereComponent>(HSPlayer);
		HeartBeatRange->RegisterComponentWithWorld(GetWorld());
		HeartBeatRange->AttachToComponent(HSPlayer->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		HeartBeatRange->SetRelativeLocation(FVector(0, 0, 0));
		HeartBeatRange->SetSphereRadius(1700);
		HeartBeatRange->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
		HeartBeatRange->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnHeartBeatRangeBeginOverlap);
		HeartBeatRange->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnHeartBeatRangeEndOverlap);
	}

	SelectedBGM = EBGMType::Normal;
	PlayBGM();
}

#pragma endregion

#pragma region Data

FAudioInfo* UHSAudioController::GetSoundData(int32 RowNum)
{
	return AudioDataTable->FindRow<FAudioInfo>(*FString::FromInt(RowNum), TEXT(""));
}

FAudioInfo* UHSAudioController::GetSoundData(FName TargetName)
{
	FAudioInfo* AudioInfo = nullptr;

	for (auto RowData : AudioDataTable->GetRowMap())
	{
		AudioInfo = (FAudioInfo*)RowData.Value;

		if (AudioInfo->Name == TargetName)
		{
			return AudioInfo;
		}
	}

	return AudioInfo;
}

void UHSAudioController::FindSounds()
{
	if (!AudioDataTable)
	{
		return;
	}

	for (int32 Index = 1; Index <= AudioDataTable->GetRowMap().Num(); Index++)
	{
		FAudioInfo* Data = GetSoundData(Index);

		FString SoundPath = Data->Path;

		if (Data->Group == FName("BGM"))
		{
			USoundWave* LoadSound = LoadObject<USoundWave>(nullptr, *SoundPath);
			BGM_Map.Add(Data->Name, LoadSound);
		}
		else if (Data->Group == FName("Anomaly"))
		{
			USoundWave* LoadSound = LoadObject<USoundWave>(nullptr, *SoundPath);
			Anomaly_Map.Add(Data->Name, LoadSound);
		}
	}
}

#pragma endregion

#pragma region BGM

void UHSAudioController::PlayBGM()
{
	if (BGM_AudioComponent->IsPlaying())
	{
		BGM_AudioComponent->Stop();
	}

	BGM_AudioComponent->Sound = BGM_Map.Find(HSEnumManager::GetEnumAsFName<EBGMType>(SelectedBGM))->Get();
	BGM_AudioComponent->Play();
}

void UHSAudioController::TagChangeEvent_Chased(FGameplayTag ChangeTag, int32 NewCount)
{
	if (ASC->HasMatchingGameplayTag(ChangeTag))
	{
		SelectedBGM = EBGMType::Chased;
	}
	else
	{
		SelectedBGM = EBGMType::Normal;
	}

	PlayBGM();
}

void UHSAudioController::TagChangeEvent_HeartBeat(FGameplayTag ChangeTag, int32 NewCount)
{
	if (ASC->HasMatchingGameplayTag(ChangeTag) && !ASC->HasMatchingGameplayTag(HSGameplayTags::State::Chased))
	{
		SelectedBGM = EBGMType::HeartBeat;
		PlayBGM();

		return;
	}

	TagChangeEvent_Chased(HSGameplayTags::State::Chased, 0);
}

void UHSAudioController::GameClearFunc()
{
	BGM_AudioComponent->OnAudioFinished.RemoveDynamic(this, &ThisClass::PlayBGM);

	SelectedBGM = EBGMType::GameClear;
	PlayBGM();
}

void UHSAudioController::TagChangeEvent_GameOver(FGameplayTag ChangeTag, int32 NewCount)
{
	BGM_AudioComponent->OnAudioFinished.RemoveDynamic(this, &ThisClass::PlayBGM);

	SelectedBGM = EBGMType::GameOver;
	PlayBGM();
}

void UHSAudioController::TagChangeEvent_Report(FGameplayTag ChangeTag, int32 NewCount)
{
	if (!ASC->HasMatchingGameplayTag(ChangeTag))
	{
		TagChangeEvent_HeartBeat(HSGameplayTags::State::HeartBeat, 0);

		return;
	}

	SelectedBGM = EBGMType::ReportResult;
	PlayBGM();
}

void UHSAudioController::OnHeartBeatRangeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->IsA(AMonster_Base::StaticClass()))
	{
		return;
	}

	ASC->AddLooseGameplayTag(HSGameplayTags::State::HeartBeat);
}

void UHSAudioController::OnHeartBeatRangeEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor->IsA(AMonster_Base::StaticClass()))
	{
		return;
	}

	ASC->RemoveLooseGameplayTag(HSGameplayTags::State::HeartBeat);
}

#pragma endregion

#pragma region Anomaly

void UHSAudioController::PlayAnomalyOccurSound(int32 CurrentAnomaly, const int32 MaxAnomaly)
{
	if (CurrentAnomaly >= MaxAnomaly)
	{
		return;
	}

	if (CurrentAnomaly < MaxAnomaly - 1)
	{
		SelectedAnomalySound = EAnomalySoundType::Occurrence;
	}
	else if (CurrentAnomaly == MaxAnomaly - 1)
	{
		SelectedAnomalySound = EAnomalySoundType::Warning;
	}

	Anomaly_AudioComponent->Sound = Anomaly_Map.Find(HSEnumManager::GetEnumAsFName<EAnomalySoundType>(SelectedAnomalySound))->Get();
	Anomaly_AudioComponent->Play();
	Anomaly_AudioComponent->StopDelayed(3);
}

#pragma endregion