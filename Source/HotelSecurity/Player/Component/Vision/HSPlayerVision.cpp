// Made by LSH

#include "Player/Component/Vision/HSPlayerVision.h"
#include "Player/Character/HSPlayer.h"
#include "Player/Controller/HSPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "AI/Character/Nurse/Nurse.h"
#include "AI/Character/Nurse/NurseInterface/NurseInterface.h"

#pragma region Base

UHSPlayerVision::UHSPlayerVision()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHSPlayerVision::BeginPlay()
{
	Super::BeginPlay();

	HSPlayer = Cast<AHSPlayer>(GetOwner());

	if (HSPlayer)
	{
		PC = Cast<AHSPlayerController>(HSPlayer->GetController());
	}

	FTimerHandle VisionHandle;
	GetWorld()->GetTimerManager().SetTimer(VisionHandle, this, &ThisClass::CheckPlayerVision, VisionDuration, true);
}

#pragma endregion

#pragma region Vision

void UHSPlayerVision::CheckPlayerVision()
{
	TArray<AActor*> FoundNurses;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UNurseInterface::StaticClass(), OUT FoundNurses);

	for (auto* FoundNurse : FoundNurses)
	{
		FVector2D ScreenPosition;
		bool bOnPlayerVision = PC->ProjectWorldLocationToScreen(FoundNurse->GetActorLocation(), OUT ScreenPosition);

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(HSPlayer);
		Params.AddIgnoredActor(FoundNurse);

		bool bHit = GetWorld()->LineTraceSingleByChannel(OUT HitResult, HSPlayer->GetActorLocation(), FoundNurse->GetActorLocation(), ECC_Visibility, Params);

		if (bOnPlayerVision && !bHit)
		{
			Cast<ANurse>(FoundNurse)->StopNurseMovement();
		}
	}
}

#pragma endregion