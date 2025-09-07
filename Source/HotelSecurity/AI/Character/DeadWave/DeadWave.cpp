// Made by LSH

#include "AI/Character/DeadWave/DeadWave.h"
#include "UI/Base/InGame/UI_InGame.h"
#include "Components/SphereComponent.h"
#include "Player/Character/HSPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/AttributeSet/AI/HSMonsterAttributeSet.h"

#pragma region Base

ADeadWave::ADeadWave(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	MonsterAS->InitWalkSpeed(150);
	MonsterAS->InitRunSpeed(350);

	GetCharacterMovement()->MaxWalkSpeed = MonsterAS->GetWalkSpeed();

	NoiseRange = CreateDefaultSubobject<USphereComponent>(TEXT("NoiseRange"));
	NoiseRange->SetupAttachment(RootComponent);
	NoiseRange->SetSphereRadius(900);
	NoiseRange->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::NoiseRangeBeginOverlap);
	NoiseRange->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::NoiseRangeBeginOverlap);
	NoiseRange->OnComponentEndOverlap.RemoveDynamic(this, &ThisClass::NoiseRangeEndOverlap);
	NoiseRange->OnComponentEndOverlap.AddDynamic(this, &ThisClass::NoiseRangeEndOverlap);

	VisibleRange = CreateDefaultSubobject<USphereComponent>(TEXT("VisibleRange"));
	VisibleRange->SetupAttachment(RootComponent);
	VisibleRange->SetSphereRadius(600);
	VisibleRange->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::VisibleRangeBeginOverlap);
	VisibleRange->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::VisibleRangeBeginOverlap);
	VisibleRange->OnComponentEndOverlap.RemoveDynamic(this, &ThisClass::VisibleRangeEndOverlap);
	VisibleRange->OnComponentEndOverlap.AddDynamic(this, &ThisClass::VisibleRangeEndOverlap);

	GetMesh()->SetVisibility(false, true);
}

#pragma endregion

#pragma region Noise

void ADeadWave::NoiseRangeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AHSPlayer::StaticClass()))
	{
		UUI_InGame::ChizizikOn.Broadcast(true);
	}
}

void ADeadWave::NoiseRangeEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AHSPlayer::StaticClass()))
	{
		UUI_InGame::ChizizikOn.Broadcast(false);
	}
}

#pragma endregion

#pragma region Visible

void ADeadWave::VisibleRangeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AHSPlayer::StaticClass()))
	{
		GetMesh()->SetVisibility(true, true);
	}
}

void ADeadWave::VisibleRangeEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AHSPlayer::StaticClass()))
	{
		GetMesh()->SetVisibility(false, true);
	}
}

#pragma endregion