// Made by LSH

#include "AI/Character/HotelManager/HotelManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/AttributeSet/AI/HSMonsterAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Character/Component/Interact/HSCharacterInteract.h"
#include "Interact/Door/HSInteractDoor.h"

#pragma region Base

AHotelManager::AHotelManager(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -120), FRotator(0, -90, 0));

	MonsterAS->InitWalkSpeed(150);
	MonsterAS->InitRunSpeed(350);

	GetCharacterMovement()->MaxWalkSpeed = MonsterAS->GetWalkSpeed();

	FaceMask = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FaceMask"));
	FaceMask->SetupAttachment(GetMesh(), FName("HeadSocket"));

	KillPlayerCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	InteractComp->SetActive(false);
	InteractComp->SetComponentTickEnabled(false);
	InteractComp->DestroyComponent();

	DoorFind = CreateDefaultSubobject<USphereComponent>(TEXT("DoorFind"));
	DoorFind->SetupAttachment(RootComponent);
	DoorFind->SetSphereRadius(800);
	DoorFind->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::DoorFindBeginOverlap);
	DoorFind->OnComponentEndOverlap.AddDynamic(this, &ThisClass::DoorFindEndOverlap);
}

#pragma endregion

#pragma region Door

void AHotelManager::DoorFindBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AHSInteractDoor* Target = Cast<AHSInteractDoor>(OtherActor))
	{
		if (!Target->bIsRotating)
		{
			return;
		}

		FindDoors.AddUnique(Cast<AActor>(Target));
	}
}

void AHotelManager::DoorFindEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AHSInteractDoor* Target = Cast<AHSInteractDoor>(OtherActor))
	{
		if (!Target->bIsRotating)
		{
			return;
		}

		FindDoors.AddUnique(Cast<AActor>(Target));
	}
}

#pragma endregion