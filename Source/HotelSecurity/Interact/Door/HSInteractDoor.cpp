// Made by LSH

#include "Interact/Door/HSInteractDoor.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"

#pragma region Base

AHSInteractDoor::AHSInteractDoor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	InteractObject->SetCanEverAffectNavigation(false);

	InteractRange->SetRelativeLocation(FVector(0, -45, 100));
	InteractRange->SetSphereRadius(90.f);

	LockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LockMesh"));
	LockMesh->SetupAttachment(RootComponent);
	LockMesh->SetVisibility(false, true);
}

#pragma endregion

#pragma region Interact

void AHSInteractDoor::InteractThisObject()
{
	if (!bCanInteract)
	{
		return;
	}

	if (bIsDoorLock)
	{
		TryDoorUnlock();

		return;
	}

	Super::InteractThisObject();

	const float RotateValue = 90;

	FRotator CurrentRotation = InteractObject->GetRelativeRotation();
	FRotator TargetRotation = CurrentRotation;

	if (bIsInteracted)
	{
		TargetRotation.Yaw = CurrentRotation.Yaw - RotateValue;
		InteractObject->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		TargetRotation.Yaw = CurrentRotation.Yaw + RotateValue;
		InteractObject->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	bIsRotating = !bIsRotating;
	bCanInteract = false;

	GetWorld()->GetTimerManager().SetTimer(RotateHandle, [this, CurrentRotation, TargetRotation]()
		{
			RotateDoor(CurrentRotation, TargetRotation);
		}, 0.01f, true);
}

void AHSInteractDoor::RotateDoor(FRotator CurrentRotation, FRotator TargetRotation)
{
	CurrentRotation = InteractObject->GetRelativeRotation();

	FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 10);

	InteractObject->SetRelativeRotation(SmoothRotation);

	if (SmoothRotation.Equals(TargetRotation, 0.01f))
	{
		bCanInteract = true;

		GetWorld()->GetTimerManager().ClearTimer(RotateHandle);
	}
}

#pragma endregion

#pragma region Lock

void AHSInteractDoor::SetDoorLock()
{
	bIsDoorLock = true;
	LockMesh->SetVisibility(true, true);
}

void AHSInteractDoor::TryDoorUnlock()
{
	InteractAC->Sound = DoorUnLockSound;
	InteractAC->Play(0.f);

	FVector TargetLocation = LockMesh->GetRelativeLocation();
	TargetLocation.Z -= 80;

	FTimerHandle SmoothHandle;
	GetWorld()->GetTimerManager().SetTimer(SmoothHandle, [this, TargetLocation]()
		{
			FVector CurrentLocation = LockMesh->GetRelativeLocation();
			FVector SmoothLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, GetWorld()->GetDeltaSeconds(), 10);

			LockMesh->SetRelativeLocation(SmoothLocation);

			if (SmoothLocation.Equals(TargetLocation, 0.01f))
			{
				bIsDoorLock = false;
				bCanInteract = true;
				LockMesh->SetVisibility(false, true);
			}
		}, 0.01f, true);
}

#pragma endregion