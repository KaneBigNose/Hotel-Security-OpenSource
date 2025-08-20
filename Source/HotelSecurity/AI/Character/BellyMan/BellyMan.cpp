// Made by LSH

#include "AI/Character/BellyMan/BellyMan.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/AttributeSet/AI/HSMonsterAttributeSet.h"

#pragma region Base

ABellyMan::ABellyMan(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -125), FRotator(0, -90, 0));
	GetMesh()->SetRelativeScale3D(FVector(45, 45, 45));

	MonsterAS->InitWalkSpeed(120);
	MonsterAS->InitRunSpeed(350);

	GetCharacterMovement()->MaxWalkSpeed = MonsterAS->GetWalkSpeed();
}

#pragma endregion