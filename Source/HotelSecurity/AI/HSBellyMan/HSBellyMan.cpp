// Made by LSH

#include "AI/HSBellyMan/HSBellyMan.h"
#include "GameFramework/CharacterMovementComponent.h"

#pragma region Base

AHSBellyMan::AHSBellyMan()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -125), FRotator(0, -90, 0));
	GetMesh()->SetRelativeScale3D(FVector(45, 45, 45));

	GetCharacterMovement()->MaxWalkSpeed = BellyManWalkSpeed;
}

#pragma endregion

#pragma region Chase

void AHSBellyMan::SetChaseTargetMode()
{
	Super::SetChaseTargetMode();

	GetCharacterMovement()->MaxWalkSpeed = BellyManRunSpeed;
}

void AHSBellyMan::SetNormalMode()
{
	Super::SetNormalMode();

	GetCharacterMovement()->MaxWalkSpeed = BellyManWalkSpeed;
}

#pragma endregion