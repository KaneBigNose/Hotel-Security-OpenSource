// Made by LSH

#include "GAS/AbilityTask/Zoom/AT_Zooming.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/Character/HSPlayer.h"
#include "Player/Component/Camera/HSPlayerCamera.h"

void UAT_Zooming::Activate()
{
	Super::Activate();

	AHSPlayer* Owner = Cast<AHSPlayer>(GetAvatarActor());
	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(Owner->GetAbilitySystemComponent());

	GetWorld()->GetTimerManager().SetTimer(ZoomHandle, [this, Owner]() {Zooming(Owner); }, 0.01f, true);
}

void UAT_Zooming::OnDestroy(bool bInOwnerFinished)
{
	GetWorld()->GetTimerManager().ClearTimer(ZoomHandle);

	Super::OnDestroy(bInOwnerFinished);
}

void UAT_Zooming::Zooming(AHSPlayer* Owner)
{
	USpringArmComponent* SpringArm = Owner->GetCameraComponent()->GetSpringArm();
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ZoomCameraArmLength, GetWorld()->GetDeltaSeconds(), CameraSpeed);
}