// Made by LSH

#include "AI/HSNurse/HSNurse.h"
#include "GameFramework/CharacterMovementComponent.h"

#pragma region Base

AHSNurse::AHSNurse()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -120), FRotator(0, -90, 0));
	GetMesh()->SetRelativeScale3D(FVector(0.15, 0.15, 0.15));

	GetCharacterMovement()->MaxWalkSpeed = NurseWalkSpeed;
}

#pragma endregion

#pragma region Stop

void AHSNurse::StopNurseMovement()
{
	CustomTimeDilation = DelayedValue;
	GetWorld()->GetTimerManager().SetTimer(StopHandle, this, &ThisClass::ResetMovement, StopDuration, false);
}

void AHSNurse::ResetMovement()
{
	CustomTimeDilation = DefaultDelayValue;
}

#pragma endregion