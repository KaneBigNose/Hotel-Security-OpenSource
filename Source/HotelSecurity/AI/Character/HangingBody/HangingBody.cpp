// Made by LSH

#include "AI/Character/HangingBody/HangingBody.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/Character/HSPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "GAS/AttributeSet/AI/HSMonsterAttributeSet.h"
#include "Character/Component/Sound/HSCharacterSound.h"

#pragma region Base

AHangingBody::AHangingBody(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	FearingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("FearingSphere"));
	FearingSphere->SetupAttachment(RootComponent);
	FearingSphere->SetSphereRadius(100.f);
	FearingSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::FearingSphereBeginOverlap);

	MonsterAS->InitWalkSpeed(180);
	MonsterAS->InitRunSpeed(180);
	MonsterAS->InitFearDamage(25);
	GetCharacterMovement()->MaxWalkSpeed = MonsterAS->GetWalkSpeed();

	KillPlayerCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DefaultSound = CreateDefaultSubobject<UHSCharacterSound>(TEXT("DefaultSound"));
}

#pragma endregion

#pragma region Overlap Event

void AHangingBody::FearingSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AHSPlayer::StaticClass()))
	{
		ASC->ActiveAbilitiesByTag(HSGameplayTags::Action::Fearing);
		ASC->ApplyGameplayEffect(Cast<AHSCharacter>(OtherActor), FearEffect, HSGameplayTags::Calculation::Fear, MonsterAS->GetFearDamage());
	}
}

#pragma endregion