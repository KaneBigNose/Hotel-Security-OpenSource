// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/Character/Monster_Base.h"
#include "TimeEater.generated.h"

UCLASS()
class HOTEL_SECURITY_API ATimeEater : public AMonster_Base
{
	GENERATED_BODY()
	
#pragma region Base

public:
	ATimeEater(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Clock;

#pragma endregion

#pragma region Overlap Event

protected:
	virtual void KillBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

#pragma endregion

#pragma region Time Stop

protected:
	UFUNCTION()
	void DestroyTimeEater(bool bIsStop);

	virtual void MonsterStop(bool bIsStop) override;

protected:
	static bool bIsTimeStop;

#pragma endregion

};