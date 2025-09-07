// Made by LSH

#include "Character/Component/Sound/HSCharacterSound.h"
#include "Components/AudioComponent.h"

UHSCharacterSound::UHSCharacterSound(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHSCharacterSound::BeginPlay()
{
	Super::BeginPlay();

	BaseAC = NewObject<UAudioComponent>(GetOwner());
	BaseAC->RegisterComponent();
	BaseAC->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	BaseAC->Sound = BaseSound;
	BaseAC->OnAudioFinished.RemoveDynamic(this, &ThisClass::PlayBaseSound);
	BaseAC->OnAudioFinished.AddDynamic(this, &ThisClass::PlayBaseSound);

	PlayBaseSound();
}

void UHSCharacterSound::PlayBaseSound()
{
	if (!BaseSound)
	{
		return;
	}

	if (BaseAC->IsPlaying())
	{
		BaseAC->Stop();
	}

	BaseAC->Play();
}