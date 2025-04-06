// Made by LSH

#include "Interact/Door/HSInteractDoor.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"

#pragma region Base

AHSInteractDoor::AHSInteractDoor()
{
	InteractRange->SetRelativeLocation(FVector(0, -45, 100));
	InteractRange->SetSphereRadius(90.f);
}

void AHSInteractDoor::BeginPlay()
{
	Super::BeginPlay();

	CurrentRotation = InteractObject->GetRelativeRotation();
	DestinationRotation = CurrentRotation;
}

void AHSInteractDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsRotating)
	{
		CurrentRotation = InteractObject->GetRelativeRotation();

		FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, DestinationRotation, DeltaTime, 5.f);

		InteractObject->SetRelativeRotation(SmoothRotation);

		if (SmoothRotation.Equals(DestinationRotation, 0.01f)) // ���� ���� ������ �� ���� ������ Ȯ���ϴ� �Լ�
		{
			bIsRotating = false;
		}
	}
}

#pragma endregion

#pragma region Interact

void AHSInteractDoor::PlayerInteractThisObject()
{
	Super::PlayerInteractThisObject();

	if (bIsInteracted)
	{
		DestinationRotation.Yaw = CurrentRotation.Yaw - RotateValue;
		InteractObject->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		DestinationRotation.Yaw = CurrentRotation.Yaw + RotateValue;
		InteractObject->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	bIsRotating = true;
}

#pragma endregion