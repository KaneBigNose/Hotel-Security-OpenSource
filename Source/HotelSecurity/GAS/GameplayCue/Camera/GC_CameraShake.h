// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GC_CameraShake.generated.h"

UCLASS()
class HOTEL_SECURITY_API UGC_CameraShake : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
	
protected:
	virtual void HandleGameplayCue(AActor* MyTarget,
								   EGameplayCueEvent::Type EventType,
								   const FGameplayCueParameters& Parameters) override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> CameraShakeClass;
};