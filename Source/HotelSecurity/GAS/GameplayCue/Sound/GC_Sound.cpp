// Made by LSH

#include "GAS/GameplayCue/Sound/GC_Sound.h"
#include "Kismet/GameplayStatics.h"

void UGC_Sound::HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters)
{
	Super::HandleGameplayCue(MyTarget, EventType, Parameters);

	if (!MyTarget || EventType != EGameplayCueEvent::Executed)
	{
		return;
	}

	UGameplayStatics::PlaySound2D(GetWorld(), Sound);
}