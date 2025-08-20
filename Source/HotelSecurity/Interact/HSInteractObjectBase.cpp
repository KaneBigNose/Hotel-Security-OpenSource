// Made by LSH

#include "Interact/HSInteractObjectBase.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"

#pragma region Base

AHSInteractObjectBase::AHSInteractObjectBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	InteractObject = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractObject"));
	InteractObject->SetRelativeScale3D(FVector(2, 2, 1.5f));
	InteractObject->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);

	SetRootComponent(InteractObject);

	InteractRange = CreateDefaultSubobject<USphereComponent>(TEXT("InteractRange"));
	InteractRange->SetupAttachment(RootComponent);
	InteractRange->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	InteractAC = CreateDefaultSubobject<UAudioComponent>(TEXT("InteractAudioComponent"));
	InteractAC->SetupAttachment(RootComponent);
}

#pragma endregion

#pragma region Interact

void AHSInteractObjectBase::InteractThisObject()
{
	bIsInteracted = !bIsInteracted;

	if (!InteractSound)
	{
		return;
	}

	InteractAC->Sound = InteractSound;
	InteractAC->Play(0.f);
}

#pragma endregion