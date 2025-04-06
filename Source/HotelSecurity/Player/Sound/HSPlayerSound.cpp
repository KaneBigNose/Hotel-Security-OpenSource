// Made by LSH

#include "Player/Sound/HSPlayerSound.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "AI/HSMonsterBase/HSMonsterBase.h"
#include "GAS/GameplayTag/HSPlayerGameplayTags.h"
#include "Components/SphereComponent.h"
#include "Subsystem/Hotel/HotelSubsystem.h"
#include "Subsystem/Mine/MineSubsystem.h"
#include "Subsystem/Hospital/HospitalSubsystem.h"

#pragma region Base

UHSPlayerSound::UHSPlayerSound()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHSPlayerSound::BeginPlay()
{
	Super::BeginPlay();

	HSPlayer = Cast<AHSPlayer>(GetOwner());

	if (!HSPlayer)
	{
		return;
	}

	FString MapName = FPaths::GetCleanFilename(GetWorld()->GetMapName());
	if (MapName.EndsWith(TEXT("Hotel")))
	{
		MapSubsystem = GetWorld()->GetSubsystem<UHotelSubsystem>();
	}
	else if (MapName.EndsWith(TEXT("Mine")))
	{
		MapSubsystem = GetWorld()->GetSubsystem<UMineSubsystem>();
	}
	else if (MapName.EndsWith(TEXT("Hospital")))
	{
		MapSubsystem = GetWorld()->GetSubsystem<UHospitalSubsystem>();
	}

	MapSubsystem->AnomalyEventOccur.AddDynamic(this, &ThisClass::PlayAnomalyEventSound);

	AnomalyEventAudioComponent = NewObject<UAudioComponent>(HSPlayer);
	EffectAudioComponent = NewObject<UAudioComponent>(HSPlayer);
	BGMAudioComponent = NewObject<UAudioComponent>(HSPlayer);
	HeartBeatAudioComponent = NewObject<UAudioComponent>(HSPlayer);
	FlashAudioComponent = NewObject<UAudioComponent>(HSPlayer);

	HSPlayer->GetHeartBeatRangeComponent()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnHeartBeatRangeBeginOverlap);
	HSPlayer->GetHeartBeatRangeComponent()->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnHeartBeatRangeEndOverlap);
}

void UHSPlayerSound::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_Chased))
	{
		SetBGMNormal();
	}

	if (!BGMAudioComponent->IsPlaying())
	{
		PlayBGM(false);
	}

	if (HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_HeartBeat))
	{
		PlayHeartBeatSound(true);
	}
	else
	{
		PlayHeartBeatSound(false);
	}
}

#pragma endregion

#pragma region Anomaly

void UHSPlayerSound::PlayAnomalyEventSound()
{
	if (MapSubsystem->GetCurrentAnomaly() < 4)
	{
		AnomalyEventAudioComponent->Sound = AnomalyOccurenceSound;
		AnomalyEventAudioComponent->Play();
	}
	else if (MapSubsystem->GetCurrentAnomaly() == 4)
	{
		AnomalyEventAudioComponent->Sound = AnomalyWarningSound;
		AnomalyEventAudioComponent->Play();
		AnomalyEventAudioComponent->StopDelayed(3.f);
	}
}

void UHSPlayerSound::StopAnomalyEventSound()
{
	AnomalyEventAudioComponent->Stop();
}

void UHSPlayerSound::PlayAnomalyFixSound()
{
	if (MapSubsystem->GetFailCount() >= MapSubsystem->GetMaxFailCount())
	{
		return;
	}

	AnomalyEventAudioComponent->Sound = AnomalyFixingSound;
	AnomalyEventAudioComponent->Play();
	AnomalyEventAudioComponent->StopDelayed(2.f);
}

#pragma endregion

#pragma region Effect

void UHSPlayerSound::PlayEffectSound(bool bIsChased, bool bStopDelayed, float DelayDuration)
{
	if (bIsChased)
	{
		EffectAudioComponent->Sound = ChasedEffectSound;
	}
	else
	{
		EffectAudioComponent->Sound = DeathEffectSound;
	}

	if (EffectAudioComponent->IsPlaying())
	{
		EffectAudioComponent->Stop();
	}

	EffectAudioComponent->Play(0.1f);

	if (bStopDelayed)
	{
		EffectAudioComponent->StopDelayed(DelayDuration);
	}
}

#pragma endregion

#pragma region BGM

void UHSPlayerSound::PlayBGM(bool bStop)
{
	if (!bStop)
	{
		BGMAudioComponent->Play(0.f);
	}
	else
	{
		BGMAudioComponent->Stop();
	}
}

#pragma endregion

#pragma region HeartBeat

void UHSPlayerSound::PlayHeartBeatSound(bool bPlaySound)
{
	HeartBeatAudioComponent->Sound = HeartBeatSound;

	if (bPlaySound)
	{
		if (!HeartBeatAudioComponent->IsPlaying())
		{
			HeartBeatAudioComponent->Play(0.1f);
		}
	}
	else
	{
		HeartBeatAudioComponent->Stop();
	}
}

void UHSPlayerSound::OnHeartBeatRangeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->IsA(AHSMonsterBase::StaticClass()))
	{
		return;
	}

	HSPlayer->GetHSPlayerStateContainer().AddTag(HSPlayerGameplayTags::HSPlayer_State_HeartBeat);
}

void UHSPlayerSound::OnHeartBeatRangeEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor->IsA(AHSMonsterBase::StaticClass()))
	{
		return;
	}

	HSPlayer->GetHSPlayerStateContainer().RemoveTag(HSPlayerGameplayTags::HSPlayer_State_HeartBeat);
}

#pragma endregion

#pragma region Flash

void UHSPlayerSound::PlayFlashEquipSound(bool bStop)
{
	if (bStop)
	{
		FlashAudioComponent->Stop();
		return;
	}

	FlashAudioComponent->Sound = FlashEquipSound;

	FlashAudioComponent->Play(0.f);

	HSPlayer->MakeNoise(FlashNoisePower, HSPlayer, HSPlayer->GetActorLocation());
}

#pragma endregion