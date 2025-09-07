// Made by LSH

#include "AI/Character/BlackVeil/BlackVeil.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interact/Light/HSInteractLight.h"
#include "Player/Character/HSPlayer.h"
#include "GAS/GameplayTag/HSGameplayTags.h"
#include "GAS/AttributeSet/AI/HSMonsterAttributeSet.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "Character/Component/Sound/HSCharacterSound.h"

#pragma region Base

ABlackVeil::ABlackVeil(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	GetCapsuleComponent()->SetCapsuleRadius(60.f);

	Body1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body1Mesh"));
	Body1Mesh->SetupAttachment(RootComponent);
	Body1Mesh->SetRelativeLocationAndRotation(FVector(0, 0, -110), FRotator(0, -90, 0));
	Body1Mesh->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));

	Body2Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body2Mesh"));
	Body2Mesh->SetupAttachment(Body1Mesh);

	MaskMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MaskMesh"));
	MaskMesh->SetupAttachment(Body1Mesh);

	MonsterAS->InitWalkSpeed(50);
	MonsterAS->InitRunSpeed(50);
	GetCharacterMovement()->MaxWalkSpeed = MonsterAS->GetWalkSpeed();

	InteractLightCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractLightCapsule"));
	InteractLightCapsule->SetupAttachment(RootComponent);
	InteractLightCapsule->SetCapsuleHalfHeight(600.f);
	InteractLightCapsule->SetCapsuleRadius(600.f);
	InteractLightCapsule->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);
	InteractLightCapsule->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnInteractRangeLightBeginOverlap);
	InteractLightCapsule->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnInteractRangeLightBeginOverlap);
	InteractLightCapsule->OnComponentEndOverlap.RemoveDynamic(this, &ThisClass::OnInteractRangeLightEndOverlap);
	InteractLightCapsule->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnInteractRangeLightEndOverlap);

	KillCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DefaultSound = CreateDefaultSubobject<UHSCharacterSound>(TEXT("DefaultSound"));
}

#pragma endregion

#pragma region Overlap Event

void ABlackVeil::OnInteractRangeLightBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AHSInteractLight* CheckObject = Cast<AHSInteractLight>(OtherActor))
	{
		if (CheckObject->IsLightTurnOn())
		{
			CheckObject->InteractThisObject();
		}
	}

	else if (AHSPlayer* HSPlayer = Cast<AHSPlayer>(OtherActor))
	{
		UHSAbilitySystemComponent* PlayerASC = Cast<UHSAbilitySystemComponent>(HSPlayer->GetAbilitySystemComponent());
		PlayerASC->AddUniqueGameplayTag(HSGameplayTags::State::FlashLock);
	}
}

void ABlackVeil::OnInteractRangeLightEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AHSInteractLight* CheckObject = Cast<AHSInteractLight>(OtherActor))
	{
		if (CheckObject->IsLightTurnOn())
		{
			CheckObject->InteractThisObject();
		}
	}

	else if (AHSPlayer* HSPlayer = Cast<AHSPlayer>(OtherActor))
	{
		UHSAbilitySystemComponent* PlayerASC = Cast<UHSAbilitySystemComponent>(HSPlayer->GetAbilitySystemComponent());
		PlayerASC->RemoveLooseGameplayTag(HSGameplayTags::State::FlashLock);
	}
}

#pragma endregion