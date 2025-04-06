// Made by LSH

#include "AI/HSHangingBody/HSHangingBody.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "Player/Camera/HSPlayerCamera.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/InGame/Fear/HSFearWidget.h"
#include "UI/InGame/HSInGameBase.h"

#pragma region Base

AHSHangingBody::AHSHangingBody()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	FearSphere = CreateDefaultSubobject<USphereComponent>(TEXT("FearSphere"));
	FearSphere->SetupAttachment(RootComponent);
	FearSphere->SetSphereRadius(100.f);
	FearSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::FearSphereBeginOverlap);

	HangingBodyAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("HangingBodyAudioComponent"));
	HangingBodyAudioComponent->SetupAttachment(RootComponent);

	GetCharacterMovement()->MaxWalkSpeed = BellyManWalkSpeed;
}

void AHSHangingBody::BeginPlay()
{
	Super::BeginPlay();

	KillPlayerCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	InteractDoorCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AHSHangingBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayHangingBodySound(BaseSound);
}

#pragma endregion

#pragma region Overlap Event

void AHSHangingBody::FearSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsOverlapped)
	{
		return;
	}

	if (OtherActor->IsA(AHSPlayer::StaticClass()))
	{
		Fearing(Cast<AHSPlayer>(OtherActor));
		GetWorld()->GetTimerManager().SetTimer(DisappearHandle, this, &ThisClass::DisappearHangingBody, DisappearDuration, false);
		bIsOverlapped = true;
	}
}

#pragma endregion

#pragma region Fear

void AHSHangingBody::Fearing(AHSPlayer* HSPlayer)
{
	bFear = true;

	HangingBodyAudioComponent->Stop();

	PlayHangingBodySound(FearSound);

	HSPlayer->GetHSPlayerCameraComponent()->MakeCameraShake(false);
	HSPlayer->MakeNoise(2.f, HSPlayer, HSPlayer->GetActorLocation());

	TArray<UUserWidget*> FoundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHSFearWidget::StaticClass(), false);

	UHSFearWidget* FearWidget = Cast<UHSFearWidget>(FoundWidgets[0]);
	FearWidget->SetVisibility(ESlateVisibility::Visible);
	FearWidget->IncreaseFearValue();
}

void AHSHangingBody::DisappearHangingBody()
{
	Destroy();
}

#pragma endregion

#pragma region Sound

void AHSHangingBody::PlayHangingBodySound(USoundWave* TargetSound)
{
	if (!TargetSound || HangingBodyAudioComponent->IsPlaying())
	{
		return;
	}

	HangingBodyAudioComponent->Sound = TargetSound;

	HangingBodyAudioComponent->Play(0.f);
}

#pragma endregion