// Made by LSH

#include "Interact/Light/HSInteractLight.h"
#include "Components/SphereComponent.h"
#include "Components/PointLightComponent.h"

#pragma region Base

AHSInteractLight::AHSInteractLight(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	InteractRange->SetRelativeLocation(FVector(0, 0, 25));
	InteractRange->SetSphereRadius(60.f);

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);
	PointLight->SetRelativeLocation(FVector(0, 0, 46.66f));
	PointLight->bAffectsWorld = true;
}

#pragma endregion

#pragma region Interact

void AHSInteractLight::InteractThisObject()
{
	Super::InteractThisObject();

	if (PointLight->bAffectsWorld)
	{
		PointLight->bAffectsWorld = false;
	}
	else
	{
		PointLight->bAffectsWorld = true;
	}

	PointLight->MarkRenderStateDirty();
}

#pragma endregion