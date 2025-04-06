// Made by LSH

#include "Player/Camera/HSPlayerCamera.h"
#include "Player/Camera/HSPlayerCameraShake.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "Player/HSPlayer/HSPlayerController.h"
#include "Player/Sound/HSPlayerSound.h"
#include "GAS/GameplayTag/HSPlayerGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

#pragma region Base

UHSPlayerCamera::UHSPlayerCamera()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHSPlayerCamera::BeginPlay()
{
	Super::BeginPlay();

	HSPlayer = Cast<AHSPlayer>(GetOwner());

	if (!HSPlayer)
	{
		return;
	}

	HSPlayer->PlayerDieDelegate.AddDynamic(this, &ThisClass::SetCameraDeathMode);

	HSPlayerController = Cast<AHSPlayerController>(HSPlayer->GetController());

	SetCameraNormalMode();
}

void UHSPlayerCamera::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsDeadCameraRotate)
	{
		FRotator CurrentRotation = HSPlayer->GetDeathViewCameraComponent()->GetComponentRotation();
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(HSPlayer->GetDeathViewCameraComponent()->GetComponentLocation(), HSPlayer->AttackerLocation);
		FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 5.0f);
		HSPlayer->GetDeathViewCameraComponent()->SetWorldRotation(SmoothRotation);
	}
}

#pragma endregion

#pragma region Camera

void UHSPlayerCamera::MakeCameraShake(bool bPlayEffectSound)
{
	if (!bPlayEffectSound)
	{
		HSPlayerController->ClientStartCameraShake(HangingBodyCameraShake);
		return;
	}

	if (HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_Chased) || !bCanCameraShake)
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(NextShakeHandle, this, &ThisClass::ResetCanShake, 10.f, false);

	bCanCameraShake = false;

	HSPlayerController->ClientStartCameraShake(HSPlayerCameraShake);

	HSPlayer->GetHSPlayerStateContainer().AddTag(HSPlayerGameplayTags::HSPlayer_State_Chased);

	HSPlayer->GetHSPlayerSoundComponent()->PlayEffectSound(true, true, 0.8f);

	HSPlayer->GetHSPlayerSoundComponent()->PlayBGM(true);
	HSPlayer->GetHSPlayerSoundComponent()->SetBGMChased();
	HSPlayer->GetHSPlayerSoundComponent()->PlayBGM(false);
}

void UHSPlayerCamera::ResetCanShake()
{
	bCanCameraShake = true;
}

void UHSPlayerCamera::SetCameraNormalMode()
{
	HSPlayer->GetCameraComponent()->SetActive(true);
	HSPlayer->GetDeathViewCameraComponent()->SetActive(false);
	bIsDeadCameraRotate = false;
}

void UHSPlayerCamera::SetCameraDeathMode(AHSMonsterBase* Attacker)
{
	HSPlayer->GetCameraComponent()->SetActive(false);
	HSPlayer->GetDeathViewCameraComponent()->SetActive(true);
	bIsDeadCameraRotate = true;
}

#pragma endregion