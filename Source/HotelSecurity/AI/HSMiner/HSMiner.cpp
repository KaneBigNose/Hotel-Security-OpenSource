// Made by LSH

#include "AI/HSMiner/HSMiner.h"
#include "AI/HSHangingBody/HSHangingBody.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#pragma region Base

AHSMiner::AHSMiner()
{
	PrimaryActorTick.bCanEverTick = true;

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

	GetCharacterMovement()->MaxWalkSpeed = MinerWalkSpeed;
}

#pragma endregion

#pragma region Chase

void AHSMiner::SetChaseTargetMode()
{
	Super::SetChaseTargetMode();

	GetCharacterMovement()->MaxWalkSpeed = MinerRunSpeed;
}

void AHSMiner::SetNormalMode()
{
	Super::SetNormalMode();

	GetCharacterMovement()->MaxWalkSpeed = MinerWalkSpeed;
}

#pragma endregion

#pragma region Summon

void AHSMiner::SummonHangingBody()
{
	if (!HangingBodyClass)
	{
		return;
	}

	GetWorld()->SpawnActor<AHSHangingBody>(HangingBodyClass, GetActorLocation(), GetActorRotation());
}

#pragma endregion