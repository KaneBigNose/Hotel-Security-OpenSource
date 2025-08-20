// Made by LSH

#include "AI/Character/PlagueDoctor/PlagueDoctor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/AttributeSet/AI/HSMonsterAttributeSet.h"

#pragma region Base

APlagueDoctor::APlagueDoctor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -120), FRotator(0, -90, 0));
	GetMesh()->SetRelativeScale3D(FVector(1.8f, 1.8f, 1.8f));

	MonsterAS->InitWalkSpeed(120);
	MonsterAS->InitRunSpeed(400);

	GetCharacterMovement()->MaxWalkSpeed = MonsterAS->GetWalkSpeed();
}

#pragma endregion