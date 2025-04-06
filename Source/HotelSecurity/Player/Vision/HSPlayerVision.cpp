// Made by LSH

#include "Player/Vision/HSPlayerVision.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "Player/HSPlayer/HSPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "AI/HSNurse/HSNurse.h"
#include "AI/HSNurse/NurseInterface/HSNurseInterface.h"

#pragma region Base

void UHSPlayerVision::BeginPlay()
{
	Super::BeginPlay();

	HSPlayer = Cast<AHSPlayer>(GetOwner());

	if (HSPlayer)
	{
		HSPlayerController = Cast<AHSPlayerController>(HSPlayer->GetController());
	}

	GetWorld()->GetTimerManager().SetTimer(VisionHandle, this, &ThisClass::CheckPlayerVision, VisionDuration, true);
}

#pragma endregion

#pragma region Vision

void UHSPlayerVision::CheckPlayerVision()
{
	TArray<AActor*> FoundNurses;

	FVector2D ScreenPosition;

	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UHSNurseInterface::StaticClass(), FoundNurses);

	for (AActor* FoundNurse : FoundNurses)
	{
		if (FoundNurse->GetClass()->ImplementsInterface(UHSNurseInterface::StaticClass()))
		{
			bool bOnPlayerVision = HSPlayerController->ProjectWorldLocationToScreen(FoundNurse->GetActorLocation(), ScreenPosition);

			FHitResult HitResult;
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(HSPlayer);
			Params.AddIgnoredActor(FoundNurse);

			GetWorld()->LineTraceSingleByChannel(
				HitResult,
				HSPlayer->GetActorLocation(),
				FoundNurse->GetActorLocation(),
				ECC_Visibility,
				Params
			);

			bool bHitWall = false;
			if (HitResult.GetActor())
			{
				bHitWall = true;
			}

			if (bOnPlayerVision && !bHitWall)
			{
				Cast<AHSNurse>(FoundNurse)->StopNurseMovement();
			}
		}
	}
}

#pragma endregion