// Made by LSH

#include "Player/Character/HSPlayer.h"
#include "Player/Component/Camera/HSPlayerCamera.h"
#include "Player/Component/Vision/HSPlayerVision.h"
#include "Player/State/HSPlayerState.h"
#include "Components/SpotLightComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameSystem/AudioController/HSAudioController.h"
#include "GameSystem/Subsystem/HSWorldSubsystem.h"
#include "GAS/AttributeSet/Player/HSPlayerAttributeSet.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/GameplayTag/HSGameplayTags.h"

#pragma region Base

AHSPlayer::AHSPlayer(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -93), FRotator(0, -90, 0));
	GetMesh()->SetVisibility(false);

	GetCapsuleComponent()->SetCapsuleHalfHeight(88);
	GetCapsuleComponent()->SetCapsuleRadius(60);

	VisionComponent = CreateDefaultSubobject<UHSPlayerVision>(TEXT("VisionComponent"));
	CameraComponent = CreateDefaultSubobject<UHSPlayerCamera>(TEXT("CameraComponent"));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0, 500, 0);

	HandFlash = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandFlash"));
	HandFlash->SetRelativeScale3D(FVector(0.03f, 0.03f, 0.03f));
	HandFlash->SetRelativeLocationAndRotation(FVector(35, 30, -15), FRotator(-90, 0, -5));
	HandFlash->SetVisibility(false);
	HandFlash->SetOnlyOwnerSee(true);

	HandFlashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("HandFlashLight"));
	HandFlashLight->SetRelativeLocationAndRotation(FVector(0, 0, 1000), FRotator(90, 0, 0));
	HandFlashLight->bAffectsWorld = false;
	HandFlashLight->OuterConeAngle = 40;
	HandFlashLight->AttenuationRadius = 2000;
	HandFlashLight->Intensity = 20000;
	HandFlashLight->IntensityUnits = ELightUnits::Unitless;
	
	PlayerDie.AddDynamic(this, &ThisClass::OnPlayerDie);
}

void AHSPlayer::BeginPlay()
{
	Super::BeginPlay();

	HandFlash->AttachToComponent(Cast<USceneComponent>(CameraComponent->GetSpringArm()), FAttachmentTransformRules::KeepRelativeTransform);

	HandFlashLight->AttachToComponent(HandFlash, FAttachmentTransformRules::KeepRelativeTransform);
}

void AHSPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AHSPlayerState* PS = GetPlayerState<AHSPlayerState>();
	UHSPlayerAttributeSet* AS = PS->GetPlayerAttributeSet();

	GetCharacterMovement()->MaxWalkSpeed = AS->GetWalkSpeed();

	ASC = Cast<UHSAbilitySystemComponent>(PS->GetAbilitySystemComponent());
	ASC->InitAbilityActorInfo(PS, this);

	GiveAbilities();

	UHSAudioController* AudioCon = GetWorld()->GetSubsystem<UHSAudioController>();
	AudioCon->AudioSetting();

	UHSWorldSubsystem* MapSub = GetWorld()->GetSubsystem<UHSWorldSubsystem>();
	MapSub->MapSetting();
}

#pragma endregion

#pragma region GAS

UHSAttributeSet* AHSPlayer::GetHSAttributeSet()
{
	AHSPlayerState* PS = GetPlayerState<AHSPlayerState>();

	return Cast<UHSAttributeSet>(PS->GetPlayerAttributeSet());
}

#pragma endregion

#pragma region Die

void AHSPlayer::OnPlayerDie(AMonster_Base* Attacker)
{
	ASC->ActiveAbilitiesByTag(HSGameplayTags::State::Die);
}

#pragma endregion