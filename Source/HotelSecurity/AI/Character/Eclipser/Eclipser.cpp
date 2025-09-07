// Made by LSH

#include "AI/Character/Eclipser/Eclipser.h"
#include "GAS/AttributeSet/AI/HSMonsterAttributeSet.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/Character/HSPlayer.h"

#pragma region Base

AEclipser::AEclipser(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	MonsterAS->InitWalkSpeed(200);
	MonsterAS->InitRunSpeed(200);

	GetCharacterMovement()->MaxWalkSpeed = MonsterAS->GetWalkSpeed();

	KillCapsule->SetCapsuleHalfHeight(200);
	KillCapsule->SetCapsuleRadius(200);

	KillCapsule->OnComponentEndOverlap.RemoveDynamic(this, &ThisClass::KillEndOverlap);
	KillCapsule->OnComponentEndOverlap.AddDynamic(this, &ThisClass::KillEndOverlap);
}

#pragma endregion

#pragma region Overlap Event

void AEclipser::KillBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AHSPlayer* HSPlayer = Cast<AHSPlayer>(OtherActor))
	{
		GetWorld()->GetTimerManager().SetTimer(BatteryHandle, [this, HSPlayer]()
			{
				ASC->ApplyGameplayEffect(Cast<AHSCharacter>(HSPlayer), BatteryEffect, HSGameplayTags::Calculation::Battery, -2);
			}, 0.1f, true);
	}
}

void AEclipser::KillEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AHSPlayer* HSPlayer = Cast<AHSPlayer>(OtherActor))
	{
		GetWorld()->GetTimerManager().ClearTimer(BatteryHandle);
	}
}

#pragma endregion