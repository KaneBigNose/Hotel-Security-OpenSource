// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "HSMakeNoise.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSMakeNoise : public UAnimNotify
{
	GENERATED_BODY()

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	UPROPERTY(EditAnywhere)
	float NoisePower = 1.f;
};