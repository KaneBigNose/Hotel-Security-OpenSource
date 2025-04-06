// Made by LSH

#include "Player/Animation/HSPlayerAnimInstance.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "Player/HSPlayer/HSPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/GameplayTag/HSPlayerGameplayTags.h"

UHSPlayerAnimInstance::UHSPlayerAnimInstance(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UHSPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	HSPlayer = Cast<AHSPlayer>(GetOwningActor());

	if (HSPlayer)
	{
		HSPlayerController = Cast<AHSPlayerController>(HSPlayer->GetController());
		HSPlayerMovementComponent = Cast<UCharacterMovementComponent>(HSPlayer->GetMovementComponent());
	}
}

void UHSPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!HSPlayer)
	{
		return;
	}

	Velocity = HSPlayerMovementComponent->Velocity;

	CurrentSpeed = Velocity.Size2D();

	bShouldMove = (CurrentSpeed > 3.f && HSPlayerMovementComponent->GetCurrentAcceleration() != FVector(0, 0, 0));

	if (HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_Sprint))
	{
		bIsSprint = true;
	}
	else
	{
		bIsSprint = false;
	}

	if (HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_SitDown))
	{
		bIsSitDown = true;
	}
	else
	{
		bIsSitDown = false;
	}
}