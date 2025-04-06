// Made by LSH

#include "AI/HSMelodia/HSMelodia.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/InGame/Fear/HSFearWidget.h"

#pragma region Base

AHSMelodia::AHSMelodia()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0, 0, 20));
	GetMesh()->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	GetCharacterMovement()->MaxWalkSpeed = MelodiaWalkSpeed;

	MelodySphere = CreateDefaultSubobject<USphereComponent>(TEXT("MelodySphere"));
	MelodySphere->SetupAttachment(RootComponent);
	MelodySphere->SetSphereRadius(1600.f);
	MelodySphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnMelodySphereBeginOverlap);
	MelodySphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnMelodySphereEndOverlap);

	MelodiaAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MelodiaAudioComponent"));
	MelodiaAudioComponent->SetupAttachment(RootComponent);
}

void AHSMelodia::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayBaseSound();
}

#pragma endregion

#pragma region Overlap Event

void AHSMelodia::OnMelodySphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AHSPlayer::StaticClass()))
	{
		GetWorld()->GetTimerManager().SetTimer(FearHandle, this, &ThisClass::IncreaseFear, 0.5f, true);
	}
}

void AHSMelodia::OnMelodySphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AHSPlayer::StaticClass()))
	{
		GetWorld()->GetTimerManager().ClearTimer(FearHandle);
	}
}

#pragma endregion

#pragma region Sound

void AHSMelodia::PlayBaseSound()
{
	if (!BaseSound || MelodiaAudioComponent->IsPlaying())
	{
		return;
	}

	MelodiaAudioComponent->Sound = BaseSound;

	MelodiaAudioComponent->Play(0.f);
}

#pragma endregion

#pragma region Fear

void AHSMelodia::IncreaseFear()
{
	TArray<UUserWidget*> FoundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHSFearWidget::StaticClass(), false);

	UHSFearWidget* FearWidget = Cast<UHSFearWidget>(FoundWidgets[0]);

	FearWidget->SetVisibility(ESlateVisibility::Visible);

	if (FearWidget->GetCurrentFearPercent() >= 1.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(FearHandle);
		return;
	}

	FearWidget->IncreaseFearValue2();
}

#pragma endregion