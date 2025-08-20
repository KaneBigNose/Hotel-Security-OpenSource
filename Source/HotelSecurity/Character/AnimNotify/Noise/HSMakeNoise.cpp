// Made by LSH

#include "Character/AnimNotify/Noise/HSMakeNoise.h"
#include "Character/Character/HSCharacter.h"

void UHSMakeNoise::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AHSCharacter* Owner = Cast<AHSCharacter>(MeshComp->GetOwner());

	if (!Owner)
	{
		return;
	}

	Owner->MakeNoise(NoisePower, Owner, Owner->GetActorLocation());
}