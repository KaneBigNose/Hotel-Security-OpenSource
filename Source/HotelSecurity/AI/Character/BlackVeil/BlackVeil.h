// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/Character/Monster_Base.h"
#include "BlackVeil.generated.h"

UCLASS()
class HOTEL_SECURITY_API ABlackVeil : public AMonster_Base
{
	GENERATED_BODY()
	
#pragma region Base

public:
	ABlackVeil(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Body1Mesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Body2Mesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> MaskMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UHSCharacterSound> DefaultSound;

#pragma endregion

#pragma region Overlap Event

protected:
	UFUNCTION()
	void OnInteractRangeLightBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnInteractRangeLightEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCapsuleComponent> InteractLightCapsule;

#pragma endregion

};