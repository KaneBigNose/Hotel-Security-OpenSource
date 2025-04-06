// Made by LSH

#include "Player/Interact/HSPlayerInteract.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/InGame/Aim/HSAimWidget.h"
#include "Interact/Door/HSInteractDoor.h"

#pragma region Base

UHSPlayerInteract::UHSPlayerInteract()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHSPlayerInteract::BeginPlay()
{
	Super::BeginPlay();

	HSPlayer = Cast<AHSPlayer>(GetOwner());

	if (!HSPlayer)
	{
		return;
	}
}

void UHSPlayerInteract::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CreateLineTrace();
}

#pragma endregion

#pragma region Interact

void UHSPlayerInteract::CreateLineTrace()
{
	TArray<FHitResult> LineTraceHits;

	FVector StartLocation = HSPlayer->GetCameraComponent()->GetComponentLocation();
	FVector EndLocation = HSPlayer->GetCameraComponent()->GetForwardVector() * LineTraceLength + StartLocation;

	ECollisionChannel LineTraceChannel = ECollisionChannel::ECC_Visibility;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(HSPlayer);

	GetWorld()->LineTraceMultiByChannel(OUT LineTraceHits, StartLocation, EndLocation, LineTraceChannel, QueryParams);

	CheckInteractObjectHitLineTrace(LineTraceHits);
}

void UHSPlayerInteract::CheckInteractObjectHitLineTrace(TArray<FHitResult> LineTraceHits)
{
	TArray<UUserWidget*> FoundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHSAimWidget::StaticClass(), false);

	UHSAimWidget* AimWidget = Cast<UHSAimWidget>(FoundWidgets[0]);

	for (auto CheckActor : LineTraceHits)
	{
		if (CheckActor.GetActor()->IsA(AHSInteractObjectBase::StaticClass()))
		{
			HitObject = Cast<AHSInteractObjectBase>(CheckActor.GetActor());
			AimWidget->ChangeInteractAim(true);
			return;
		}
	}

	AimWidget->ChangeInteractAim(false);
	HitObject = nullptr;
}

void UHSPlayerInteract::CanInteractTimer()
{
	bCanInteract = false;
	GetWorld()->GetTimerManager().SetTimer(CanInteractHandle, this, &ThisClass::CanInteract, 1.f, false);
}

void UHSPlayerInteract::CanInteract()
{
	bCanInteract = true;
}

#pragma endregion