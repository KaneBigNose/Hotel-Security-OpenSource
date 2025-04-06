// Made by LSH

#include "AI/HSBlackVeil/HSBlackVeil.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Interact/Light/HSInteractLight.h"
#include "Interact/Door/HSInteractDoor.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "GAS/GameplayTag/HSPlayerGameplayTags.h"
#include "Components/AudioComponent.h"

#pragma region Base

AHSBlackVeil::AHSBlackVeil()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleRadius(60.f);

	BlackVeilMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackVeilMesh"));
	BlackVeilMesh->SetupAttachment(RootComponent);
	BlackVeilMesh->SetRelativeLocationAndRotation(FVector(0, 0, -110), FRotator(0, -90, 0));
	BlackVeilMesh->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));

	GetCharacterMovement()->MaxWalkSpeed = BlackVeilWalkSpeed;

	InteractLightCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractLightCapsule"));
	InteractLightCapsule->SetupAttachment(RootComponent);
	InteractLightCapsule->SetCapsuleHalfHeight(600.f);
	InteractLightCapsule->SetCapsuleRadius(600.f);
	InteractLightCapsule->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

	InteractLightCapsule->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnInteractRangeLightBeginOverlap);
	InteractLightCapsule->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnInteractRangeLightEndOverlap);

	BlackVeilAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BlackVeilAudioComponent"));
	BlackVeilAudioComponent->SetupAttachment(RootComponent);
}

void AHSBlackVeil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayBaseSound();
}

#pragma endregion

#pragma region Overlap Event

void AHSBlackVeil::OnInteractRangeLightBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AHSInteractLight::StaticClass()))
	{
		InInteractRangeLights.AddUnique(Cast<AHSInteractLight>(OtherActor));
	}

	else if (OtherActor->IsA(AHSPlayer::StaticClass()))
	{
		AHSPlayer* HSPlayer = Cast<AHSPlayer>(OtherActor);
		HSPlayer->GetHSPlayerStateContainer().AddTag(HSPlayerGameplayTags::HSPlayer_State_FlashLock);
	}
}

void AHSBlackVeil::OnInteractRangeLightEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AHSInteractLight::StaticClass()))
	{
		InInteractRangeLights.Remove(Cast<AHSInteractLight>(OtherActor));
	}

	else if (OtherActor->IsA(AHSPlayer::StaticClass()))
	{
		AHSPlayer* HSPlayer = Cast<AHSPlayer>(OtherActor);
		HSPlayer->GetHSPlayerStateContainer().RemoveTag(HSPlayerGameplayTags::HSPlayer_State_FlashLock);
	}
}

#pragma endregion

#pragma region Sound

void AHSBlackVeil::PlayBaseSound()
{
	if (!BaseSound || BlackVeilAudioComponent->IsPlaying())
	{
		return;
	}

	BlackVeilAudioComponent->Sound = BaseSound;

	BlackVeilAudioComponent->Play(0.f);
}

#pragma endregion