// Made by LSH

#include "AI/Character/Miner/Miner.h"
#include "AI/Character/HangingBody/HangingBody.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/AttributeSet/AI/HSMonsterAttributeSet.h"

#pragma region Base

AMiner::AMiner(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(150.f);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -152), FRotator(0, -90, 0));
	GetMesh()->SetRelativeScale3D(FVector(4, 4, 4));

	Helmet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Helmet"));
	Helmet->SetupAttachment(GetMesh(), FName("HelmetSocket"));

	HelmetFlash = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HelmetFlash"));
	HelmetFlash->SetupAttachment(GetMesh(), FName("HelmetFlashSocket"));

	PickAx = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickAx"));
	PickAx->SetupAttachment(GetMesh(), FName("PickAxSocket"));
	PickAx->SetActive(false);

	FlashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("FlashLight"));
	FlashLight->SetupAttachment(GetMesh(), FName("SpotLightSocket"));

	StartLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("StartLight"));
	StartLight->SetupAttachment(GetMesh(), FName("SpotLightSocket"));

	MonsterAS->InitWalkSpeed(180);
	MonsterAS->InitRunSpeed(350);

	GetCharacterMovement()->MaxWalkSpeed = MonsterAS->GetWalkSpeed();
}

#pragma endregion

#pragma region Summon

void AMiner::SummonHangingBody()
{
	if (!HangingBodyClass)
	{
		return;
	}

	GetWorld()->SpawnActor<AHangingBody>(HangingBodyClass, GetActorLocation(), GetActorRotation());
}

#pragma endregion