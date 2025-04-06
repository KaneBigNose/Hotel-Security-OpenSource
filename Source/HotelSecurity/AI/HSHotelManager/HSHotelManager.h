// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/HSMonsterBase/HSMonsterBase.h"
#include "HSHotelManager.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSHotelManager : public AHSMonsterBase
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AHSHotelManager();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* FaceMask;

#pragma endregion

#pragma region Calculate

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HotelManagerWalkSpeed = 150.f;

#pragma endregion

#pragma region Pass

public:
	UFUNCTION()
	void OnPassRangeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	class AHSInteractDoor* PassDoor;

	FTimerHandle DoorPassHandle;

	void ReturnPassDoor();

#pragma endregion

};