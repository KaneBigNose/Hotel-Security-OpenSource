// Made by LSH

#include "Player/Component/Camera/HSPlayerCamera.h"
#include "Player/Character/HSPlayer.h"
#include "AI/Character/Monster_Base.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

#pragma region Base

UHSPlayerCamera::UHSPlayerCamera()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHSPlayerCamera::BeginPlay()
{
	Super::BeginPlay();

	HSPlayer = Cast<AHSPlayer>(GetOwner());
	HSPlayer->PlayerDie.RemoveDynamic(this, &ThisClass::SetCameraDieView);
	HSPlayer->PlayerDie.AddDynamic(this, &ThisClass::SetCameraDieView);

	SpringArm = NewObject<USpringArmComponent>(HSPlayer);
	SpringArm->RegisterComponent();
	SpringArm->AttachToComponent(HSPlayer->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("head"));
	SpringArm->SetRelativeLocation(FVector(0, 0, 0));
	SpringArm->TargetArmLength = 0.f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bDoCollisionTest = true;
	SpringArm->ProbeChannel = ECC_Pawn;
	SpringArm->ProbeSize = 50;

	Camera = NewObject<UCameraComponent>(HSPlayer);
	Camera->RegisterComponent();
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
	Camera->SetRelativeLocation(FVector(0, 0, 0));
	Camera->bUsePawnControlRotation = true;
}

void UHSPlayerCamera::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(RotateHandle);

	Super::EndPlay(EndPlayReason);
}

#pragma endregion

#pragma region Camera

void UHSPlayerCamera::SetCameraDieView(AMonster_Base* Attacker)
{
	SpringArm->bUsePawnControlRotation = false;
	Camera->bUsePawnControlRotation = false;

	if (!Attacker)
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(RotateHandle, [this, Attacker]()
		{
			RotateToAttacker(Attacker);
		}, 0.01f, true);
}

void UHSPlayerCamera::RotateToAttacker(AMonster_Base* Attacker)
{
	FRotator CurrentRotation = SpringArm->GetComponentRotation();
	FVector AttackerLocation = Attacker->GetActorLocation();
	AttackerLocation.Z += 50;
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(SpringArm->GetComponentLocation(), AttackerLocation);
	FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, 0.01f, 5.0f);

	SpringArm->SetWorldRotation(SmoothRotation);

	if (SmoothRotation.Equals(TargetRotation, 0.01f))
	{
		GetWorld()->GetTimerManager().ClearTimer(RotateHandle);
	}
}

#pragma endregion