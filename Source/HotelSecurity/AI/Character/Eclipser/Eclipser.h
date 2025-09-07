// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/Character/Monster_Base.h"
#include "Eclipser.generated.h"

UCLASS()
class HOTEL_SECURITY_API AEclipser : public AMonster_Base
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AEclipser(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Overlap Event

protected:
	virtual void KillBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION()
	void KillEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	FTimerHandle BatteryHandle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameplayEffect> BatteryEffect;

#pragma endregion

};