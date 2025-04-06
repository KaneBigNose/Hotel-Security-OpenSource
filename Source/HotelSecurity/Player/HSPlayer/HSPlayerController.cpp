// Made by LSH

#include "Player/HSPlayer/HSPlayerController.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "Player/Interact/HSPlayerInteract.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UI/Report/HSReportBaseWidget.h"
#include "UI/InGame/Pause/HSPauseWidget.h"
#include "GAS/GameplayTag/HSPlayerGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "Components/SpotLightComponent.h"
#include "Interact/Door/HSInteractDoor.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameInstance/HSGameInstance.h"

#pragma region Base

void AHSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HSPlayer = Cast<AHSPlayer>(GetPawn());

	if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMCDefault, 0);
	}

	GameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	SettingWidget();
}

void AHSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IAMove, ETriggerEvent::Triggered, this, &ThisClass::MoveTriggered);
		EnhancedInputComponent->BindAction(IAMove, ETriggerEvent::Completed, this, &ThisClass::MoveReleased);
		EnhancedInputComponent->BindAction(IAMove, ETriggerEvent::Canceled, this, &ThisClass::MoveReleased);

		EnhancedInputComponent->BindAction(IALook, ETriggerEvent::Triggered, this, &ThisClass::LookTriggered);
		EnhancedInputComponent->BindAction(IALook, ETriggerEvent::Completed, this, &ThisClass::LookReleased);
		EnhancedInputComponent->BindAction(IALook, ETriggerEvent::Canceled, this, &ThisClass::LookReleased);

		EnhancedInputComponent->BindAction(IAInteract, ETriggerEvent::Started, this, &ThisClass::InteractStarted);

		EnhancedInputComponent->BindAction(IASprint, ETriggerEvent::Triggered, this, &ThisClass::SprintTriggered);
		EnhancedInputComponent->BindAction(IASprint, ETriggerEvent::Completed, this, &ThisClass::SprintReleased);
		EnhancedInputComponent->BindAction(IASprint, ETriggerEvent::Canceled, this, &ThisClass::SprintReleased);

		EnhancedInputComponent->BindAction(IASitDown, ETriggerEvent::Started, this, &ThisClass::SitDownStarted);

		EnhancedInputComponent->BindAction(IAFlash, ETriggerEvent::Started, this, &ThisClass::FlashStarted);

		EnhancedInputComponent->BindAction(IAZoom, ETriggerEvent::Triggered, this, &ThisClass::ZoomTriggered);
		EnhancedInputComponent->BindAction(IAZoom, ETriggerEvent::Completed, this, &ThisClass::ZoomReleased);
		EnhancedInputComponent->BindAction(IAZoom, ETriggerEvent::Canceled, this, &ThisClass::ZoomReleased);

		EnhancedInputComponent->BindAction(IAReport, ETriggerEvent::Started, this, &ThisClass::ReportStarted);

		EnhancedInputComponent->BindAction(IAEscape, ETriggerEvent::Started, this, &ThisClass::EscapeStarted);

		EnhancedInputComponent->BindAction(IAEnter, ETriggerEvent::Started, this, &ThisClass::EnterStarted);
	}
}

#pragma endregion

#pragma region Widget

void AHSPlayerController::SettingWidget()
{
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;

	ReportWidget = Cast<UHSReportBaseWidget>(CreateWidget(GetWorld(), ReportUIClass));

	ReportWidget->ReportCancelEvent.AddDynamic(this, &ThisClass::CloseReportUI);

	PauseWidget = Cast<UHSPauseWidget>(CreateWidget(GetWorld(), PauseUIClass));
}

#pragma endregion

#pragma region Move

void AHSPlayerController::MoveTriggered(const FInputActionValue& InputValue)
{
	if (HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_Zoom) ||
		HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_Die))
	{
		return;
	}

	FVector2D MovementVector = InputValue.Get<FVector2D>();

	FRotator Rotator = GetControlRotation();

	if (MovementVector.X != 0)
	{
		HSPlayer->GetHSPlayerStateContainer().AddTag(HSPlayerGameplayTags::HSPlayer_State_Move);
		FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.X);
	}

	if (MovementVector.Y != 0)
	{
		HSPlayer->GetHSPlayerStateContainer().AddTag(HSPlayerGameplayTags::HSPlayer_State_Move);
		FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.Y);
	}
}

void AHSPlayerController::MoveReleased(const FInputActionValue& InputValue)
{
	HSPlayer->GetHSPlayerStateContainer().RemoveTag(HSPlayerGameplayTags::HSPlayer_State_Move);
}

#pragma endregion

#pragma region Look

void AHSPlayerController::LookTriggered(const FInputActionValue& InputValue)
{
	if (HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_Zoom) ||
		HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_Die))
	{
		return;
	}

	FVector2D LookAxisVector = InputValue.Get<FVector2D>();

	HSPlayer->GetHSPlayerStateContainer().AddTag(HSPlayerGameplayTags::HSPlayer_State_Look);

	HSPlayer->AddControllerYawInput(LookAxisVector.X * MouseSensitivity);
	HSPlayer->AddControllerPitchInput(LookAxisVector.Y * MouseSensitivity);
}

void AHSPlayerController::LookReleased(const FInputActionValue& InputValue)
{
	HSPlayer->GetHSPlayerStateContainer().RemoveTag(HSPlayerGameplayTags::HSPlayer_State_Look);
}

#pragma endregion

#pragma region Interact

void AHSPlayerController::InteractStarted(const FInputActionValue& InputValue)
{
	if (HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_Die) ||
		!HSPlayer->GetHSPlayerInteractComponent()->GetLineTraceHitObject() ||
		!HSPlayer->GetHSPlayerInteractComponent()->PlayerCanInteract())
	{
		return;
	}

	HSPlayer->GetHSPlayerInteractComponent()->GetLineTraceHitObject()->PlayerInteractThisObject();
	HSPlayer->GetHSPlayerInteractComponent()->CanInteractTimer();
}

#pragma endregion

#pragma region Sprint

void AHSPlayerController::SprintTriggered(const FInputActionValue& InputValue)
{
	if (HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_SitDown))
	{
		return;
	}

	HSPlayer->GetHSPlayerStateContainer().AddTag(HSPlayerGameplayTags::HSPlayer_State_Sprint);
	HSPlayer->GetCharacterMovement()->MaxWalkSpeed = HSPlayer->PlayerRunSpeed;
}

void AHSPlayerController::SprintReleased(const FInputActionValue& InputValue)
{
	HSPlayer->GetHSPlayerStateContainer().RemoveTag(HSPlayerGameplayTags::HSPlayer_State_Sprint);
	HSPlayer->GetCharacterMovement()->MaxWalkSpeed = HSPlayer->PlayerWalkSpeed;
}

#pragma endregion

#pragma region Flash

void AHSPlayerController::FlashStarted(const FInputActionValue& InputValue)
{
	if (HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_Die) ||
		HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_ESC))
	{
		return;
	}

	if (HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_Flash))
	{
		HSPlayer->SetFlashOnOffMode(false);
		HSPlayer->GetHSPlayerStateContainer().RemoveTag(HSPlayerGameplayTags::HSPlayer_State_Flash);
	}
	else
	{
		HSPlayer->SetFlashOnOffMode(true);
		HSPlayer->GetHSPlayerStateContainer().AddTag(HSPlayerGameplayTags::HSPlayer_State_Flash);
	}
}

#pragma endregion

#pragma region Zoom

void AHSPlayerController::ZoomTriggered(const FInputActionValue& InputValue)
{
	if (HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_Die))
	{
		return;
	}

	if (HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_Flash))
	{
		HSPlayer->SetFlashOnOffMode(false);
		HSPlayer->GetHSPlayerStateContainer().RemoveTag(HSPlayerGameplayTags::HSPlayer_State_Flash);
	}

	HSPlayer->GetHSPlayerStateContainer().AddTag(HSPlayerGameplayTags::HSPlayer_State_Zoom);

	HSPlayer->GetSpringArmComponent()->TargetArmLength = FMath::Clamp<float>(HSPlayer->GetSpringArmComponent()->TargetArmLength - HSPlayer->CameraSpeed, HSPlayer->ZoomCameraArmLength, HSPlayer->CameraArmLength);
}

void AHSPlayerController::ZoomReleased(const FInputActionValue& InputValue)
{
	HSPlayer->GetHSPlayerStateContainer().RemoveTag(HSPlayerGameplayTags::HSPlayer_State_Zoom);

	HSPlayer->GetSpringArmComponent()->TargetArmLength = HSPlayer->CameraArmLength;
}

#pragma endregion

#pragma region UI

void AHSPlayerController::ReportStarted(const FInputActionValue& InputValue)
{
	if (HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_Die) ||
		HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_Report))
	{
		return;
	}

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetWidgetToFocus(ReportWidget->TakeWidget());
	SetInputMode(InputMode);
	bShowMouseCursor = true;

	UGameplayStatics::SetGamePaused(GetWorld(), true);
	ReportWidget->AddToViewport();
	HSPlayer->GetHSPlayerStateContainer().AddTag(HSPlayerGameplayTags::HSPlayer_State_Report);

	Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->SetCurrentOpenWidget(ReportWidget);
}

void AHSPlayerController::CloseReportUI()
{
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;

	UGameplayStatics::SetGamePaused(GetWorld(), false);
	ReportWidget->RemoveFromParent();
	HSPlayer->GetHSPlayerStateContainer().RemoveTag(HSPlayerGameplayTags::HSPlayer_State_Report);
}

void AHSPlayerController::ResetReportUI()
{
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;

	UGameplayStatics::SetGamePaused(GetWorld(), false);
	ReportWidget->RemoveFromParent();
}

void AHSPlayerController::EscapeStarted(const FInputActionValue& InputValue)
{
	if (HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_Die))
	{
		return;
	}

	if (!GameInstance->GetCurrentOpenWidget())
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetWidgetToFocus(PauseWidget->TakeWidget());
		SetInputMode(InputMode);
		bShowMouseCursor = true;

		PauseWidget->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		GameInstance->SetCurrentOpenWidget(PauseWidget);

		HSPlayer->GetHSPlayerStateContainer().AddTag(HSPlayerGameplayTags::HSPlayer_State_ESC);
	}
	else
	{
		if (!GameInstance->GetCurrentOpenWidget()->GetClass()->ImplementsInterface(UHSUIInterface::StaticClass()))
		{
			return;
		}

		Cast<IHSUIInterface>(GameInstance->GetCurrentOpenWidget())->EscapeCurrentWidget();
		GameInstance->SetCurrentOpenWidget(nullptr);

		HSPlayer->GetHSPlayerStateContainer().RemoveTag(HSPlayerGameplayTags::HSPlayer_State_ESC);
	}
}

void AHSPlayerController::EnterStarted(const FInputActionValue& InputValue)
{
	if (!GameInstance->GetCurrentOpenWidget())
	{
		return;
	}

	if (!GameInstance->GetCurrentOpenWidget()->GetClass()->ImplementsInterface(UHSUIInterface::StaticClass()))
	{
		return;
	}

	Cast<IHSUIInterface>(GameInstance->GetCurrentOpenWidget())->EnterCurrentWidget();

	HSPlayer->GetHSPlayerStateContainer().RemoveTag(HSPlayerGameplayTags::HSPlayer_State_ESC);
}

#pragma endregion

#pragma region SitDown

void AHSPlayerController::SitDownStarted(const FInputActionValue& InputValue)
{
	if (!bCanSitDown || HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_Die))
	{
		return;
	}

	bCanSitDown = false;
	SitDownTimer();

	if (HSPlayer->GetHSPlayerStateContainer().HasTag(HSPlayerGameplayTags::HSPlayer_State_SitDown))
	{
		HSPlayer->GetHSPlayerStateContainer().RemoveTag(HSPlayerGameplayTags::HSPlayer_State_SitDown);
		HSPlayer->GetCharacterMovement()->MaxWalkSpeed = HSPlayer->PlayerWalkSpeed;
	}
	else
	{
		HSPlayer->GetHSPlayerStateContainer().AddTag(HSPlayerGameplayTags::HSPlayer_State_SitDown);
		HSPlayer->GetCharacterMovement()->MaxWalkSpeed = HSPlayer->PlayerCrouchedSpeed;
	}
}

void AHSPlayerController::SitDownTimer()
{
	GetWorldTimerManager().SetTimer(SitDownCoolDownHandle, this, &ThisClass::SitDownButtonTrue, SidDownCoolDown, false);
}

void AHSPlayerController::SitDownButtonTrue()
{
	bCanSitDown = true;
}

#pragma endregion