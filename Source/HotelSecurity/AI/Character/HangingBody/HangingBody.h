// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/Character/Monster_Base.h"
#include "HangingBody.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHangingBody : public AMonster_Base
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AHangingBody(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UHSCharacterSound> DefaultSound;

#pragma endregion

#pragma region Overlap Event

protected:
	UFUNCTION()
	void FearingSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USphereComponent> FearingSphere;

#pragma endregion

#pragma region Fear

protected:
	UPROPERTY(EditAnywhere, Category = "Fear")
	TSubclassOf<class UGameplayEffect> FearEffect;

#pragma endregion

};