// Made by LSH

#include "Character/Component/Interact/HSCharacterInteract.h"
#include "Camera/CameraComponent.h"
#include "Interact/Door/HSInteractDoor.h"
#include "Player/Character/HSPlayer.h"
#include "Player/Component/Camera/HSPlayerCamera.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/GameplayTag/HSGameplayTags.h"

#pragma region Base

UHSCharacterInteract::UHSCharacterInteract()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHSCharacterInteract::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AHSCharacter>(GetOwner());
}

void UHSCharacterInteract::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CreateLineTrace();
}

#pragma endregion

#pragma region Interact

void UHSCharacterInteract::CreateLineTrace()
{
	FVector StartLocation;
	FVector EndLocation;

	float LineTraceLength = 200.f;

	if (Owner->IsA(AHSPlayer::StaticClass()))
	{
		StartLocation = Cast<AHSPlayer>(Owner)->GetCameraComponent()->GetCamera()->GetComponentLocation();
		EndLocation = Cast<AHSPlayer>(Owner)->GetCameraComponent()->GetCamera()->GetForwardVector() * LineTraceLength + StartLocation;
	}
	else
	{
		StartLocation = Owner->GetActorLocation();
		EndLocation = StartLocation + Owner->GetActorForwardVector() * LineTraceLength;
	}

	FHitResult LineTraceHit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Owner);

	bool bHit = GetWorld()->LineTraceSingleByChannel(OUT LineTraceHit, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, QueryParams);

	if (bHit)
	{
		CheckInteractObjectHitLineTrace(LineTraceHit);
	}
	else
	{
		HitObject = nullptr;
		CanInteract.Broadcast(false);
	}
}

void UHSCharacterInteract::CheckInteractObjectHitLineTrace(const FHitResult& LineTraceHit)
{
	if (Owner->IsA(AHSPlayer::StaticClass()))
	{
		if (AHSInteractObjectBase* Target = Cast<AHSInteractObjectBase>(LineTraceHit.GetActor()))
		{
			HitObject = Target;
			CanInteract.Broadcast(true);

			return;
		}

		HitObject = nullptr;
		CanInteract.Broadcast(false);
	}
	else
	{
		if (AHSInteractDoor* Target = Cast<AHSInteractDoor>(LineTraceHit.GetActor()))
		{
			HitObject = Target;

			UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(Owner->GetAbilitySystemComponent());
			ASC->ActiveAbilitiesByTag(HSGameplayTags::Action::Interact);

			return;
		}
		
		HitObject = nullptr;
	}
}

#pragma endregion