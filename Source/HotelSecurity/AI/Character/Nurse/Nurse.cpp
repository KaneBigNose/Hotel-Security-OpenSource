// Made by LSH

#include "AI/Character/Nurse/Nurse.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/AttributeSet/AI/HSMonsterAttributeSet.h"

#pragma region Base

ANurse::ANurse(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -120), FRotator(0, -90, 0));
	GetMesh()->SetRelativeScale3D(FVector(0.15, 0.15, 0.15));

	MonsterAS->InitWalkSpeed(60);
	MonsterAS->InitRunSpeed(60);

	GetCharacterMovement()->MaxWalkSpeed = MonsterAS->GetWalkSpeed();
}

#pragma endregion

#pragma region Stop

void ANurse::StopNurseMovement()
{
	CustomTimeDilation = DelayedValue;
	GetWorld()->GetTimerManager().SetTimer(StopHandle, [this]() { CustomTimeDilation = DefaultDelayValue; }, 1, false);
}

#pragma endregion