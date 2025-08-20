// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/Character/Monster_Base.h"
#include "HotelManager.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHotelManager : public AMonster_Base
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AHotelManager(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> FaceMask;

#pragma endregion

#pragma region Door

protected:
	UFUNCTION()
	void DoorFindBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void DoorFindEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USphereComponent> DoorFind;

public:
	UPROPERTY()
	TArray<TObjectPtr<AActor>> FindDoors;

#pragma endregion

};