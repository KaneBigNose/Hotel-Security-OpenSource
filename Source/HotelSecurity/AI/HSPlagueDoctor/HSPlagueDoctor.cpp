// Made by LSH

#include "AI/HSPlagueDoctor/HSPlagueDoctor.h"
#include "GameFramework/CharacterMovementComponent.h"

#pragma region Base

AHSPlagueDoctor::AHSPlagueDoctor()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -120), FRotator(0, -90, 0));
	GetMesh()->SetRelativeScale3D(FVector(1.8f, 1.8f, 1.8f));

	GetCharacterMovement()->MaxWalkSpeed = PlagueDoctorWalkSpeed;
}

#pragma endregion

#pragma region Chase

void AHSPlagueDoctor::SetChaseTargetMode()
{
	Super::SetChaseTargetMode();

	GetCharacterMovement()->MaxWalkSpeed = PlagueDoctorRunSpeed;
}

void AHSPlagueDoctor::SetNormalMode()
{
	Super::SetNormalMode();

	GetCharacterMovement()->MaxWalkSpeed = PlagueDoctorWalkSpeed;
}

#pragma endregion