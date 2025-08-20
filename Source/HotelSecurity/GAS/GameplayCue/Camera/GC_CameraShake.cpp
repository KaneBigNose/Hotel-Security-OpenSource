// Made by LSH

#include "GAS/GameplayCue/Camera/GC_CameraShake.h"
#include "Character/Character/HSCharacter.h"

void UGC_CameraShake::HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters)
{
	Super::HandleGameplayCue(MyTarget, EventType, Parameters);

	if (!MyTarget || EventType != EGameplayCueEvent::Executed)
	{
		return;
	}

	AHSCharacter* Target = Cast<AHSCharacter>(MyTarget);
	APlayerController* PC = Cast<APlayerController>(Target->GetController());

	PC->ClientStartCameraShake(CameraShakeClass);
}