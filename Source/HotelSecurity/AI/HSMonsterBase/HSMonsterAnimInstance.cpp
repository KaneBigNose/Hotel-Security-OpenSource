// Made by LSH

#include "AI/HSMonsterBase/HSMonsterAnimInstance.h"
#include "AI/HSMonsterBase/HSMonsterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

#pragma region Base

void UHSMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	HSMonster = Cast<AHSMonsterBase>(GetOwningActor());

	if (HSMonster)
	{
		HSMonsterMovementComponent = Cast<UCharacterMovementComponent>(HSMonster->GetMovementComponent());
	}
}

void UHSMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!HSMonster)
	{
		return;
	}

	Velocity = HSMonsterMovementComponent->Velocity;

	CurrentSpeed = Velocity.Size2D();

	bIsMove = (CurrentSpeed > 3.f && HSMonsterMovementComponent->GetCurrentAcceleration() != FVector::ZeroVector);

	bIsSprint = HSMonster->CheckChase();
}

#pragma endregion