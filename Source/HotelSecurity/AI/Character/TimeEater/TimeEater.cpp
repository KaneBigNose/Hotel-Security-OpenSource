// Made by LSH

#include "AI/Character/TimeEater/TimeEater.h"
#include "Components/CapsuleComponent.h"
#include "GAS/AttributeSet/AI/HSMonsterAttributeSet.h"
#include "GameSystem/GameMode/HSGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/Character/HSPlayer.h"

#pragma region Base

bool ATimeEater::bIsTimeStop = false;

ATimeEater::ATimeEater(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Clock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Clock"));
	Clock->SetupAttachment(GetMesh(), FName("RightHand_Socket"));

	MonsterAS->InitWalkSpeed(250);
	MonsterAS->InitRunSpeed(250);

	GetCharacterMovement()->MaxWalkSpeed = MonsterAS->GetWalkSpeed();
}

void ATimeEater::BeginPlay()
{
	Super::BeginPlay();

	AHSGameMode* GameMode = GetWorld()->GetAuthGameMode<AHSGameMode>();
	GameMode->TimeStop.RemoveDynamic(this, &ThisClass::DestroyTimeEater);
	GameMode->TimeStop.AddDynamic(this, &ThisClass::DestroyTimeEater);

	if (bIsTimeStop)
	{
		return;
	}

	bIsTimeStop = true;

	GameMode->TimeStop.Broadcast(true);
}

#pragma endregion

#pragma region Overlap Event

void ATimeEater::KillBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AHSPlayer* HSPlayer = Cast<AHSPlayer>(OtherActor))
	{
		KillCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		AHSGameMode* GameMode = GetWorld()->GetAuthGameMode<AHSGameMode>();
		GameMode->GivePenalty();

		Destroy();
	}
}

#pragma endregion

#pragma region Time Stop

void ATimeEater::DestroyTimeEater(bool bIsStop)
{
	if (bIsStop)
	{
		return;
	}

	bIsTimeStop = false;

	Destroy();
}

void ATimeEater::MonsterStop(bool bIsStop)
{

}

#pragma endregion