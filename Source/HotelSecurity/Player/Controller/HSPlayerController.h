// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Delegates/DelegateCombinations.h"
#include "HSPlayerController.generated.h"

#pragma region Declare

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

#pragma endregion

UCLASS()
class HOTEL_SECURITY_API AHSPlayerController : public APlayerController
{
	GENERATED_BODY()

#pragma region Base

public:
	AHSPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

protected:
	UPROPERTY()
	TObjectPtr<class AHSPlayer> HSPlayer;

	UPROPERTY()
	TObjectPtr<class UHSAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<class UHSGameInstance> GameInstance;

#pragma endregion

#pragma region Input

protected:
	void MoveTriggered(const FInputActionValue& InputValue);
	void MoveReleased(const FInputActionValue& InputValue);

	void LookTriggered(const FInputActionValue& InputValue);
	void LookReleased(const FInputActionValue& InputValue);

	void InteractStarted(const FInputActionValue& InputValue);

	void RunStarted(const FInputActionValue& InputValue);
	void RunReleased(const FInputActionValue& InputValue);

	void FlashStarted(const FInputActionValue& InputValue);

	void ZoomStarted(const FInputActionValue& InputValue);
	void ZoomReleased(const FInputActionValue& InputValue);

	void ReportStarted(const FInputActionValue& InputValue);

	void EscapeStarted(const FInputActionValue& InputValue);

protected:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> IMC_Default;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Interact;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Run;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Flash;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Zoom;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Report;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Escape;

#pragma endregion

#pragma region Camera

protected:
	FVector CameraCurrentLocation = FVector(0, 30, 45);
	FRotator CameraCurrentRotation = FRotator(0, 0, 0);

	FVector CameraZoomLocation = FVector(300, 30, 45);
	FRotator CameraZoomRotation = FRotator(0, 0, 0);

#pragma endregion

};