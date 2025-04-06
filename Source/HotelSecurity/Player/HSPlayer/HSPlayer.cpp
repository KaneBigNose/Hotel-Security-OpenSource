// Made by LSH

#include "Player/HSPlayer/HSPlayer.h"
#include "Player/HSPlayer/HSPlayerController.h"
#include "Player/Camera/HSPlayerCameraShake.h"
#include "Player/Sound/HSPlayerSound.h"
#include "Player/Vision/HSPlayerVision.h"
#include "Player/Camera/HSPlayerCamera.h"
#include "Player/Interact/HSPlayerInteract.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/InGame/FlashBattery/HSFlashWidget.h"
#include "UI/GameOver/HSGameOver.h"
#include "Subsystem/Hotel/HotelSubsystem.h"
#include "Subsystem/Mine/MineSubsystem.h"
#include "Subsystem/Hospital/HospitalSubsystem.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GAS/GameplayTag/HSPlayerGameplayTags.h"
#include "AI/HSMonsterBase/HSMonsterBase.h"
#include "GameInstance/HSGameInstance.h"

#pragma region Base

AHSPlayer::AHSPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -93), FRotator(0, -90, 0));
	GetMesh()->SetVisibility(true);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh(), FName("HeadSocket"));
	SpringArm->SetRelativeLocationAndRotation(FVector(-80, 30, 0), FRotator(0, 0, 0));
	SpringArm->TargetArmLength = 0.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetRelativeLocation(FVector(-100, 0, 100));
	Camera->bUsePawnControlRotation = true;

	DeathViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("DeathViewCamera"));
	DeathViewCamera->SetupAttachment(RootComponent);
	DeathViewCamera->SetRelativeLocation(FVector(0, 0, 90));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = PlayerWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = PlayerCrouchedSpeed;

	HandFlash = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandFlash"));
	HandFlash->SetupAttachment(SpringArm);
	HandFlash->SetRelativeScale3D(FVector(0.03f, 0.03f, 0.03f));
	HandFlash->SetRelativeLocationAndRotation(FVector(-60, 30, 80), FRotator(-90, 0, 0));
	HandFlash->SetVisibility(false);
	HandFlash->SetOnlyOwnerSee(true);

	HandFlashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("HandFlashLight"));
	HandFlashLight->SetupAttachment(HandFlash);
	HandFlashLight->SetRelativeLocationAndRotation(FVector(0, 0, 1000), FRotator(90, 0, 0));
	HandFlashLight->bAffectsWorld = false;
	HandFlashLight->OuterConeAngle = 20.f;

	HeartBeatRange = CreateDefaultSubobject<USphereComponent>(TEXT("HeartBeatRange"));
	HeartBeatRange->SetupAttachment(RootComponent);
	HeartBeatRange->SetSphereRadius(HeartBeatRangeRadius);

	HSPlayerSoundComponent = CreateDefaultSubobject<UHSPlayerSound>(TEXT("HSPlayerSoundComponent"));

	HSPlayerVisionComponent = CreateDefaultSubobject<UHSPlayerVision>(TEXT("HSPlayerVisionComponent"));

	HSPlayerCameraComponent = CreateDefaultSubobject<UHSPlayerCamera>(TEXT("HSPlayerCameraComponent"));

	HSPlayerInteractComponent = CreateDefaultSubobject<UHSPlayerInteract>(TEXT("HSPlayerInteractComponent"));
}

void AHSPlayer::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	HSPlayerController = Cast<AHSPlayerController>(GetController());

	SetFlashOnOffMode(false);

	FString MapName = FPaths::GetCleanFilename(GetWorld()->GetMapName());
	if (MapName.EndsWith(TEXT("Hotel")))
	{
		MapSubsystem = GetWorld()->GetSubsystem<UHotelSubsystem>();
	}
	else if (MapName.EndsWith(TEXT("Mine")))
	{
		MapSubsystem = GetWorld()->GetSubsystem<UMineSubsystem>();
	}
	else if (MapName.EndsWith(TEXT("Hospital")))
	{
		MapSubsystem = GetWorld()->GetSubsystem<UHospitalSubsystem>();
	}

	PlayerDieDelegate.AddDynamic(this, &ThisClass::OnPlayerDie);
	PlayerDieDelegate.AddDynamic(this, &ThisClass::ChangeDieSound);

	FTimerHandle FirstHandle;

	HSPlayerStateContainer.AddTag(HSPlayerGameplayTags::HSPlayer_State_Die);

	GetWorld()->GetTimerManager().SetTimer(FirstHandle, [this]()
		{
			HSPlayerStateContainer.RemoveTag(HSPlayerGameplayTags::HSPlayer_State_Die);
		}, 3.0f, false);
}

void AHSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HSPlayerStateContainer.HasTag(HSPlayerGameplayTags::HSPlayer_State_FlashLock) || FlashLife <= 0)
	{
		HandFlashLight->bAffectsWorld = false;
		HandFlashLight->MarkRenderStateDirty();
	}
	else if (!HSPlayerStateContainer.HasTag(HSPlayerGameplayTags::HSPlayer_State_FlashLock) &&
		HSPlayerStateContainer.HasTag(HSPlayerGameplayTags::HSPlayer_State_Flash))
	{
		HandFlashLight->bAffectsWorld = true;
		HandFlashLight->MarkRenderStateDirty();
	}
}

#pragma endregion

#pragma region Die

void AHSPlayer::OnPlayerDie(AHSMonsterBase* Attacker)
{
	HSPlayerStateContainer.AddTag(HSPlayerGameplayTags::HSPlayer_State_Die);

	if (!Attacker)
	{
		if (HSPlayerStateContainer.HasTag(HSPlayerGameplayTags::HSPlayer_State_Fear))
		{
			if (GameInstance->GetSelectedLanguage() == FName("English"))
			{
				GetWorld()->GetTimerManager().SetTimer(DieHandle, FTimerDelegate::CreateLambda([this]() {this->CreateDieWidget(FText::FromString(FString(TEXT("You fainted in Fear")))); }), 2.f, false);
			}
			else if (GameInstance->GetSelectedLanguage() == FName("Korean"))
			{
				GetWorld()->GetTimerManager().SetTimer(DieHandle, FTimerDelegate::CreateLambda([this]() {this->CreateDieWidget(FText::FromString(FString(TEXT("겁에 질려 기절하였습니다")))); }), 2.f, false);
			}
		}
		else
		{
			if (GameInstance->GetSelectedLanguage() == FName("English"))
			{
				GetWorld()->GetTimerManager().SetTimer(DieHandle, FTimerDelegate::CreateLambda([this]() {this->CreateDieWidget(FText::FromString(FString(TEXT("You are Fired")))); }), 2.f, false);
			}
			else if (GameInstance->GetSelectedLanguage() == FName("Korean"))
			{
				GetWorld()->GetTimerManager().SetTimer(DieHandle, FTimerDelegate::CreateLambda([this]() {this->CreateDieWidget(FText::FromString(FString(TEXT("해고당하였습니다")))); }), 2.f, false);
			}
		}

		return;
	}

	AttackerLocation = FVector(Attacker->GetActorLocation().X, Attacker->GetActorLocation().Y, Attacker->GetActorLocation().Z + 50);

	if (GameInstance->GetSelectedLanguage() == FName("English"))
	{
		GetWorld()->GetTimerManager().SetTimer(DieHandle, FTimerDelegate::CreateLambda([this]() {this->CreateDieWidget(FText::FromString(FString(TEXT("You Died")))); }), 2.f, false);
	}
	else if (GameInstance->GetSelectedLanguage() == FName("Korean"))
	{
		GetWorld()->GetTimerManager().SetTimer(DieHandle, FTimerDelegate::CreateLambda([this]() {this->CreateDieWidget(FText::FromString(FString(TEXT("사망하였습니다")))); }), 2.f, false);
	}
}

void AHSPlayer::CreateDieWidget(FText DyingMessage)
{
	UHSGameOver* GameOverWidget = Cast<UHSGameOver>(CreateWidget(GetWorld(), GameOverClass));
	GameOverWidget->AddToViewport();
	GameOverWidget->SetDyingMessage(DyingMessage);

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetWidgetToFocus(GameOverWidget->TakeWidget());
	HSPlayerController->SetInputMode(InputMode);
	HSPlayerController->bShowMouseCursor = true;

	HSPlayerSoundComponent->PlayBGM(true);

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AHSPlayer::ChangeDieSound(AHSMonsterBase* Attacker)
{
	HSPlayerSoundComponent->PlayEffectSound(false, false);
	HSPlayerSoundComponent->StopAnomalyEventSound();
	HSPlayerSoundComponent->PlayBGM(true);
	HSPlayerSoundComponent->PlayFlashEquipSound(true);
}

#pragma endregion

#pragma region Flash

void AHSPlayer::SetFlashOnOffMode(bool bTurnOnFlash)
{
	if (FlashLife > 0 && bTurnOnFlash)
	{
		HandFlashLight->bAffectsWorld = true;
	}
	else
	{
		HandFlashLight->bAffectsWorld = false;
	}

	HandFlash->SetVisibility(bTurnOnFlash);

	HSPlayerSoundComponent->PlayFlashEquipSound(false);

	FlashLifeTimer(!bTurnOnFlash);
}

void AHSPlayer::FlashLifeTimer(bool bStop)
{
	if (bStop)
	{
		GetWorldTimerManager().ClearTimer(FlashLifeSpanHandle);
	}
	else
	{
		GetWorldTimerManager().SetTimer(FlashLifeSpanHandle, this, &ThisClass::FlashLifeSpan, 0.5f, true);
	}

	bStop = !bStop;
}

void AHSPlayer::FlashLifeSpan()
{
	if (FlashLife <= 0)
	{
		return;
	}

	FlashLife -= 0.5;

	TArray<UUserWidget*> FoundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHSFlashWidget::StaticClass(), false);

	UHSFlashWidget* FlashWidget = Cast<UHSFlashWidget>(FoundWidgets[0]);
	FlashWidget->CheckFlashBattery(FlashLife / MaxFlashLife * 100);
}

#pragma endregion