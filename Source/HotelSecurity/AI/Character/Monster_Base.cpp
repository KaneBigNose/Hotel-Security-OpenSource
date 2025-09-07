// Made by LSH

#include "AI/Character/Monster_Base.h"
#include "GAS/AttributeSet/AI/HSMonsterAttributeSet.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameSystem/GameMode/HSGameMode.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/Character/HSPlayer.h"

#pragma region Base

AMonster_Base::AMonster_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bUseControllerRotationYaw = false;

	GetCapsuleComponent()->SetCapsuleHalfHeight(120);
	GetCapsuleComponent()->SetCapsuleRadius(40);

	KillCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("KillPlayerCapsule"));
	KillCapsule->SetupAttachment(RootComponent);
	KillCapsule->SetCapsuleHalfHeight(100);
	KillCapsule->SetCapsuleRadius(60);
	KillCapsule->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::KillBeginOverlap);
	KillCapsule->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::KillBeginOverlap);

	GetCharacterMovement()->RotationRate = FRotator(0, 500, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	MonsterAS = CreateDefaultSubobject<UHSMonsterAttributeSet>(TEXT("MonsterAttributeSet"));
	MonsterAS->InitWalkSpeed(100);
	MonsterAS->InitRunSpeed(200);

	ASC = CreateDefaultSubobject<UHSAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	ASC->AddAttributeSetSubobject(MonsterAS.Get());
}

void AMonster_Base::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ASC->InitAbilityActorInfo(this, this);

	GiveAbilities();

	KillType = KillCapsule->GetCollisionEnabled();

	AHSGameMode* GameMode = GetWorld()->GetAuthGameMode<AHSGameMode>();
	GameMode->TimeStop.RemoveDynamic(this, &ThisClass::MonsterStop);
	GameMode->TimeStop.AddDynamic(this, &ThisClass::MonsterStop);
}

#pragma endregion

#pragma region GAS

UHSAttributeSet* AMonster_Base::GetHSAttributeSet()
{
	return Cast<UHSAttributeSet>(MonsterAS);
}

#pragma endregion

#pragma region Overlap Event

void AMonster_Base::KillBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AHSPlayer* HSPlayer = Cast<AHSPlayer>(OtherActor))
	{
		HSPlayer->PlayerDie.Broadcast(this);

		FRotator DestinationRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), HSPlayer->GetActorLocation());
		SetActorRotation(DestinationRotation);

		KillCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

#pragma endregion

#pragma region Time Stop

void AMonster_Base::MonsterStop(bool bIsStop)
{
	if (bIsStop)
	{
		KillCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CustomTimeDilation = 0;
	}
	else
	{
		KillCapsule->SetCollisionEnabled(KillType);
		CustomTimeDilation = 1;
	}
}

#pragma endregion