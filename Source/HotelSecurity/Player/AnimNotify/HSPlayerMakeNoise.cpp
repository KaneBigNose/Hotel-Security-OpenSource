// Made by LSH

#include "Player/AnimNotify/HSPlayerMakeNoise.h"
#include "Player/HSPlayer/HSPlayer.h"

void UHSPlayerMakeNoise::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AHSPlayer* HSPlayer = Cast<AHSPlayer>(MeshComp->GetOwner());

	if (!HSPlayer)
	{
		return;
	}

	HSPlayer->MakeNoise(NoisePower, HSPlayer, HSPlayer->GetActorLocation());
}