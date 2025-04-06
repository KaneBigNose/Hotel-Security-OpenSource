// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/HSMonsterBase/HSMonsterBase.h"
#include "HSBlackVeil.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSBlackVeil : public AHSMonsterBase
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AHSBlackVeil();

protected:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* BlackVeilMesh;

#pragma endregion

#pragma region Overlap Event

public:
	UFUNCTION()
	void OnInteractRangeLightBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnInteractRangeLightEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	TArray<class AHSInteractLight*> GetInInteractRangeLights() { return InInteractRangeLights; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* InteractLightCapsule;

	UPROPERTY()
	TArray<class AHSInteractLight*> InInteractRangeLights;

#pragma endregion

#pragma region Calculate

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlackVeilWalkSpeed = 50.f;

#pragma endregion

#pragma region Sound

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class UAudioComponent* BlackVeilAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundWave* BaseSound;

	void PlayBaseSound();

#pragma endregion

};