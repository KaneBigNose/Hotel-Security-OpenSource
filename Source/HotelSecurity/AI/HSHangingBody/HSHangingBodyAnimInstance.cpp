// Made by LSH

#include "AI/HSHangingBody/HSHangingBodyAnimInstance.h"
#include "AI/HSHangingBody/HSHangingBody.h"

#pragma region Base

void UHSHangingBodyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!HSMonster)
	{
		return;
	}

	bFear = Cast<AHSHangingBody>(HSMonster)->GetIsFearing();
}

#pragma endregion