// Made by LSH

#include "UI/MainMenu/MainMenuController/HSMainMenuController.h"
#include "UI/MainMenu/HSMainMenu.h"
#include "UI/Interface/HSUIInterface.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameInstance/HSGameInstance.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

void AHSMainMenuController::BeginPlay()
{
	Super::BeginPlay();

	TArray<UUserWidget*> FoundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHSMainMenu::StaticClass(), false);

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetWidgetToFocus(Cast<UHSMainMenu>(FoundWidgets[0])->TakeWidget());
	SetInputMode(InputMode);
	bShowMouseCursor = true;

	if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_UI, 0);
	}

	GameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void AHSMainMenuController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IAEnter, ETriggerEvent::Started, this, &ThisClass::EnterStarted);

		EnhancedInputComponent->BindAction(IAEscape, ETriggerEvent::Started, this, &ThisClass::EscapeStarted);
	}
}

#pragma endregion

#pragma region Input

void AHSMainMenuController::EnterStarted(const FInputActionValue& InputValue)
{
	// 위젯 실행 여부 체크
	if (!GameInstance->GetCurrentOpenWidget())
	{
		return;
	}

	// 인터페이스 포함 여부 체크
	if (!GameInstance->GetCurrentOpenWidget()->GetClass()->ImplementsInterface(UHSUIInterface::StaticClass()))
	{
		return;
	}

	Cast<IHSUIInterface>(GameInstance->GetCurrentOpenWidget())->EnterCurrentWidget();
}

void AHSMainMenuController::EscapeStarted(const FInputActionValue& InputValue)
{
	// 위젯 실행 여부 체크
	if (!GameInstance->GetCurrentOpenWidget())
	{
		return;
	}

	// 인터페이스 포함 여부 체크
	if (!GameInstance->GetCurrentOpenWidget()->GetClass()->ImplementsInterface(UHSUIInterface::StaticClass()))
	{
		return;
	}

	Cast<IHSUIInterface>(GameInstance->GetCurrentOpenWidget())->EscapeCurrentWidget();
	GameInstance->SetCurrentOpenWidget(nullptr);
}

#pragma endregion