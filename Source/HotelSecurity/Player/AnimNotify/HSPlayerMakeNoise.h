// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "HSPlayerMakeNoise.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSPlayerMakeNoise : public UAnimNotify
{
	GENERATED_BODY()

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float NoisePower = 1.f;
};