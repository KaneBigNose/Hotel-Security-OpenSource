// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/Character/Monster_Base.h"
#include "DeadWave.generated.h"

UCLASS()
class HOTEL_SECURITY_API ADeadWave : public AMonster_Base
{
	GENERATED_BODY()
	
#pragma region Base

public:
	ADeadWave(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USphereComponent> NoiseRange;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USphereComponent> VisibleRange;

#pragma endregion

#pragma region Noise

protected:
	UFUNCTION()
	void NoiseRangeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void NoiseRangeEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#pragma endregion

#pragma region Visible

protected:
	UFUNCTION()
	void VisibleRangeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void VisibleRangeEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#pragma endregion

};