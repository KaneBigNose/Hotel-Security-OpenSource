// Made by LSH

#include "AI/HSHotelManager/HSHotelManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Interact/Door/HSInteractDoor.h"

#pragma region Base

AHSHotelManager::AHSHotelManager()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -120), FRotator(0, -90, 0));
	GetMesh()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	GetCharacterMovement()->MaxWalkSpeed = HotelManagerWalkSpeed;

	FaceMask = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FaceMask"));
	FaceMask->SetupAttachment(GetMesh(), FName("HeadSocket"));

	InteractDoorCapsule->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnPassRangeBeginOverlap);
}

#pragma endregion

#pragma region Pass

void AHSHotelManager::OnPassRangeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AHSInteractDoor::StaticClass()))
	{
		PassDoor = Cast<AHSInteractDoor>(OtherActor);
		PassDoor->GetInteractObject()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetWorld()->GetTimerManager().SetTimer(DoorPassHandle, this, &ThisClass::ReturnPassDoor, 2.f, false);
	}
}

void AHSHotelManager::ReturnPassDoor()
{
	PassDoor->GetInteractObject()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

#pragma endregion