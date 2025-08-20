// Made by LSH

#include "Player/Controller/HSPlayerController.h"
#include "Player/Character/HSPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameSystem/GameInstance/HSGameInstance.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/GameplayTag/HSGameplayTags.h"

#pragma region Base

AHSPlayerController::AHSPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!HSPlayer)
	{
		HSPlayer = Cast<AHSPlayer>(GetPawn());
		ASC = Cast<UHSAbilitySystemComponent>(HSPlayer->GetAbilitySystemComponent());
	}

	if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_Default, 0);
	}

	GameInstance = GetWorld()->GetGameInstance<UHSGameInstance>();
}

void AHSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (auto* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::MoveTriggered);
		EIC->BindAction(IA_Move, ETriggerEvent::Completed, this, &ThisClass::MoveReleased);
		EIC->BindAction(IA_Move, ETriggerEvent::Canceled, this, &ThisClass::MoveReleased);

		EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ThisClass::LookTriggered);
		EIC->BindAction(IA_Look, ETriggerEvent::Completed, this, &ThisClass::LookReleased);
		EIC->BindAction(IA_Look, ETriggerEvent::Canceled, this, &ThisClass::LookReleased);

		EIC->BindAction(IA_Interact, ETriggerEvent::Started, this, &ThisClass::InteractStarted);

		EIC->BindAction(IA_Run, ETriggerEvent::Started, this, &ThisClass::RunStarted);
		EIC->BindAction(IA_Run, ETriggerEvent::Completed, this, &ThisClass::RunReleased);
		EIC->BindAction(IA_Run, ETriggerEvent::Canceled, this, &ThisClass::RunReleased);

		EIC->BindAction(IA_Flash, ETriggerEvent::Started, this, &ThisClass::FlashStarted);

		EIC->BindAction(IA_Zoom, ETriggerEvent::Started, this, &ThisClass::ZoomStarted);
		EIC->BindAction(IA_Zoom, ETriggerEvent::Completed, this, &ThisClass::ZoomReleased);
		EIC->BindAction(IA_Zoom, ETriggerEvent::Canceled, this, &ThisClass::ZoomReleased);

		EIC->BindAction(IA_Report, ETriggerEvent::Started, this, &ThisClass::ReportStarted);

		EIC->BindAction(IA_Escape, ETriggerEvent::Started, this, &ThisClass::EscapeStarted);
	}
}

#pragma endregion

#pragma region Move

void AHSPlayerController::MoveTriggered(const FInputActionValue& InputValue)
{
	if (ASC->HasMatchingGameplayTag(HSGameplayTags::Action::Zoom) ||
		ASC->HasMatchingGameplayTag(HSGameplayTags::State::Die))
	{
		return;
	}

	ASC->AddUniqueGameplayTag(HSGameplayTags::State::Move);

	FVector2D MovementVector = InputValue.Get<FVector2D>();
	FRotator InputRotator = GetControlRotation();

	if (MovementVector != FVector2D::ZeroVector)
	{
		FVector ForwardDirection = UKismetMathLibrary::GetForwardVector(FRotator(0, InputRotator.Yaw, 0));
		HSPlayer->AddMovementInput(ForwardDirection, MovementVector.X);

		FVector RightDirection = UKismetMathLibrary::GetRightVector(FRotator(0, InputRotator.Yaw, 0));
		HSPlayer->AddMovementInput(RightDirection, MovementVector.Y);
	}
}

void AHSPlayerController::MoveReleased(const FInputActionValue& InputValue)
{
	ASC->RemoveLooseGameplayTag(HSGameplayTags::State::Move);
}

#pragma endregion

#pragma region Look

void AHSPlayerController::LookTriggered(const FInputActionValue& InputValue)
{
	if (ASC->HasMatchingGameplayTag(HSGameplayTags::Action::Zoom) ||
		ASC->HasMatchingGameplayTag(HSGameplayTags::State::Die))
	{
		return;
	}

	ASC->AddUniqueGameplayTag(HSGameplayTags::State::Look);

	FVector2D LookVector = InputValue.Get<FVector2D>();

	if (LookVector != FVector2D::ZeroVector)
	{
		HSPlayer->AddControllerYawInput(LookVector.X);
		HSPlayer->AddControllerPitchInput(LookVector.Y);
	}
}

void AHSPlayerController::LookReleased(const FInputActionValue& InputValue)
{
	ASC->RemoveLooseGameplayTag(HSGameplayTags::State::Look);
}

#pragma endregion

#pragma region Interact

void AHSPlayerController::InteractStarted(const FInputActionValue& InputValue)
{
	ASC->ActiveAbilitiesByTag(HSGameplayTags::Action::Interact);
}

#pragma endregion

#pragma region Sprint

void AHSPlayerController::RunStarted(const FInputActionValue& InputValue)
{
	ASC->ActiveAbilitiesByTag(HSGameplayTags::State::Run);
}

void AHSPlayerController::RunReleased(const FInputActionValue& InputValue)
{
	ASC->CancelAbilitiesByTag(HSGameplayTags::State::Run);
}

#pragma endregion

#pragma region Flash

void AHSPlayerController::FlashStarted(const FInputActionValue& InputValue)
{
	ASC->ActiveAbilitiesByTag(HSGameplayTags::Action::Flash);
}

#pragma endregion

#pragma region Zoom

void AHSPlayerController::ZoomStarted(const FInputActionValue& InputValue)
{
	ASC->ActiveAbilitiesByTag(HSGameplayTags::Action::Zoom);
}

void AHSPlayerController::ZoomReleased(const FInputActionValue& InputValue)
{
	ASC->CancelAbilitiesByTag(HSGameplayTags::Action::Zoom);
}

#pragma endregion

#pragma region UI

void AHSPlayerController::ReportStarted(const FInputActionValue& InputValue)
{
	ASC->ActiveAbilitiesByTag(HSGameplayTags::UI::PopUp::Report);
}

void AHSPlayerController::EscapeStarted(const FInputActionValue& InputValue)
{
	ASC->ActiveAbilitiesByTag(HSGameplayTags::UI::Action::ESC);
}

#pragma endregion