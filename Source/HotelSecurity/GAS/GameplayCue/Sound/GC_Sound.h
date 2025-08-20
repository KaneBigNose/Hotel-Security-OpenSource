// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GC_Sound.generated.h"

UCLASS()
class HOTEL_SECURITY_API UGC_Sound : public UGameplayCueNotify_Static
{
	GENERATED_BODY()

protected:
	virtual void HandleGameplayCue(AActor* MyTarget,
								   EGameplayCueEvent::Type EventType,
								   const FGameplayCueParameters& Parameters) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundWave> Sound;
};