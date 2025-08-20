// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/Character/Monster_Base.h"
#include "Melodia.generated.h"

UCLASS()
class HOTEL_SECURITY_API AMelodia : public AMonster_Base
{
	GENERATED_BODY()

#pragma region Base

public:
	AMelodia(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> MelodiaBody;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UHSCharacterSound> DefaultSound;

#pragma endregion

#pragma region Overlap Event

protected:
	UFUNCTION()
	void OnMelodySphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnMelodySphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USphereComponent> MelodySphere;

#pragma endregion

#pragma region Fear

protected:
	FTimerHandle FearHandle;

	void IncreaseFear(class AHSCharacter* Target);

protected:
	UPROPERTY(EditAnywhere, Category = "Fear")
	TSubclassOf<class UGameplayEffect> FearEffect;

#pragma endregion

};