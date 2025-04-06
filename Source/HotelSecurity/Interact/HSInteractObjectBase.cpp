// Made by LSH

#include "Interact/HSInteractObjectBase.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"

#pragma region Base

AHSInteractObjectBase::AHSInteractObjectBase()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractObject = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractObject"));
	RootComponent = InteractObject;
	InteractObject->SetRelativeScale3D(FVector(2, 2, 1.5f));
	InteractObject->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	InteractRange = CreateDefaultSubobject<USphereComponent>(TEXT("InteractRange"));
	InteractRange->SetupAttachment(RootComponent);

	InteractAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("InteractAudioComponent"));
	InteractAudioComponent->SetupAttachment(RootComponent);
}

#pragma endregion

#pragma region Interact

void AHSInteractObjectBase::PlayerInteractThisObject()
{
	bIsInteracted = !bIsInteracted;

	if (!InteractSound)
	{
		return;
	}

	InteractAudioComponent->Sound = InteractSound;
	InteractAudioComponent->Play(0.f);
}

#pragma endregion