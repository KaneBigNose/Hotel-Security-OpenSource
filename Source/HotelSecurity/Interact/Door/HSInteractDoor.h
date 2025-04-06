// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Interact/HSInteractObjectBase.h"
#include "Interact/Door/Interface/HSInteractDoorInterface.h"
#include "HSInteractDoor.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSInteractDoor : public AHSInteractObjectBase, public IHSInteractDoorInterface
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AHSInteractDoor();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

#pragma endregion

#pragma region Interact

public:
	virtual void PlayerInteractThisObject() override;

public:
	bool DoorIsRotated() { return bIsInteracted; }

protected:
	FRotator CurrentRotation;
	FRotator DestinationRotation;

	bool bIsRotating = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	float RotateValue = 90;

#pragma endregion

};