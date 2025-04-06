// Made by LSH

#include "AI/HSMonsterBase/HSMonsterBase.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Interact/Door/HSInteractDoor.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "Kismet/KismetMathLibrary.h"

#pragma region Base

AHSMonsterBase::AHSMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;

	GetCapsuleComponent()->SetCapsuleHalfHeight(120.f);
	GetCapsuleComponent()->SetCapsuleRadius(40.f);

	KillPlayerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("KillPlayerCapsule"));
	KillPlayerCapsule->SetupAttachment(RootComponent);
	KillPlayerCapsule->SetCapsuleHalfHeight(100.f);
	KillPlayerCapsule->SetCapsuleRadius(60.f);

	KillPlayerCapsule->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnKillPlayerRangeBeginOverlap);

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->bOrientRotationToMovement = true;

	InteractDoorCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractDoorCapsule"));
	InteractDoorCapsule->SetupAttachment(RootComponent);
	InteractDoorCapsule->SetRelativeLocationAndRotation(FVector(90, 0, 0), FRotator(90, 0, 0));
	InteractDoorCapsule->SetCapsuleHalfHeight(150.f);
	InteractDoorCapsule->SetCapsuleRadius(25.f);

	InteractDoorCapsule->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnInteractRangeDoorBeginOverlap);
	InteractDoorCapsule->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnInteractRangeDoorEndOverlap);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

#pragma endregion

#pragma region Overlap Event

void AHSMonsterBase::OnKillPlayerRangeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AHSPlayer::StaticClass()))
	{
		AHSPlayer* HSPlayer = Cast<AHSPlayer>(OtherActor);
		HSPlayer->PlayerDieDelegate.Broadcast(this);

		FRotator DestinationRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), HSPlayer->GetActorLocation());
		SetActorRotation(DestinationRotation);
	}
}

void AHSMonsterBase::OnInteractRangeDoorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AHSInteractDoor::StaticClass()))
	{
		InInteractRangeDoors.AddUnique(Cast<AHSInteractDoor>(OtherActor));
	}
}

void AHSMonsterBase::OnInteractRangeDoorEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AHSInteractDoor::StaticClass()))
	{
		InInteractRangeDoors.Remove(Cast<AHSInteractDoor>(OtherActor));
	}
}

#pragma endregion

#pragma region Chase

void AHSMonsterBase::SetChaseTargetMode()
{
	bIsChased = true;
}

void AHSMonsterBase::SetNormalMode()
{
	bIsChased = false;
}

#pragma endregion