// Made by LSH

#include "AI/Character/Melodia/Melodia.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "GAS/AttributeSet/AI/HSMonsterAttributeSet.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/Character/HSPlayer.h"
#include "Character/Component/Sound/HSCharacterSound.h"

#pragma region Base

AMelodia::AMelodia(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	GetMesh()->SetRelativeLocation(FVector(0, 0, 20));
	GetMesh()->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	MonsterAS->InitWalkSpeed(40);
	MonsterAS->InitRunSpeed(40);
	MonsterAS->InitFearDamage(0.25f);

	GetCharacterMovement()->MaxWalkSpeed = MonsterAS->GetWalkSpeed();

	MelodiaBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MelodiaBody"));
	MelodiaBody->SetupAttachment(RootComponent);

	MelodySphere = CreateDefaultSubobject<USphereComponent>(TEXT("MelodySphere"));
	MelodySphere->SetupAttachment(RootComponent);
	MelodySphere->SetSphereRadius(1600.f);
	MelodySphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnMelodySphereBeginOverlap);
	MelodySphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnMelodySphereEndOverlap);

	KillPlayerCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DefaultSound = CreateDefaultSubobject<UHSCharacterSound>(TEXT("DefaultSound"));
}

#pragma endregion

#pragma region Overlap Event

void AMelodia::OnMelodySphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AHSPlayer::StaticClass()))
	{
		GetWorld()->GetTimerManager().SetTimer(FearHandle, [this, OtherActor]()
			{
				IncreaseFear(Cast<AHSCharacter>(OtherActor));
			}, 0.1f, true);
	}
}

void AMelodia::OnMelodySphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AHSPlayer::StaticClass()))
	{
		GetWorld()->GetTimerManager().ClearTimer(FearHandle);
	}
}

#pragma endregion

#pragma region Fear

void AMelodia::IncreaseFear(AHSCharacter* Target)
{
	ASC->ApplyGameplayEffect(Target, FearEffect, HSGameplayTags::Calculation::Fear, MonsterAS->GetFearDamage());
}

#pragma endregion