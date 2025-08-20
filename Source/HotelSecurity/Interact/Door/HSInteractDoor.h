// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Interact/HSInteractObjectBase.h"
#include "HSInteractDoor.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSInteractDoor : public AHSInteractObjectBase
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AHSInteractDoor(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Interact

public:
	virtual void InteractThisObject() override;

	void RotateDoor(FRotator CurrentRotation, FRotator TargetRotation);

public:
	bool bIsRotating = false;

protected:
	FTimerHandle RotateHandle;

	bool bCanInteract = true;

#pragma endregion

#pragma region Lock

public:
	void SetDoorLock();

protected:
	void TryDoorUnlock();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> LockMesh;

	UPROPERTY(EditAnywhere, Category = "Interact")
	TObjectPtr<class USoundWave> DoorUnLockSound;

	bool bIsDoorLock = false;

#pragma endregion

};