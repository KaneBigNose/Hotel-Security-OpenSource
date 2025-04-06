// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Delegates/DelegateCombinations.h"
#include "HSPlayerController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

UCLASS()
class HOTEL_SECURITY_API AHSPlayerController : public APlayerController
{
	GENERATED_BODY()

#pragma region Base

public:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AHSPlayer* HSPlayer;

	class UHSGameInstance* GameInstance;

#pragma endregion

#pragma region Widget
	
public:
	void SettingWidget();

#pragma endregion

#pragma region Camera

public:
	float MouseSensitivity = 1.f;

protected:
	FVector CameraCurrentLocation = FVector(0, 30, 45);
	FRotator CameraCurrentRotation = FRotator(0, 0, 0);

	FVector CameraZoomLocation = FVector(300, 30, 45);
	FRotator CameraZoomRotation = FRotator(0, 0, 0);

#pragma endregion

#pragma region Input

protected:
	void MoveTriggered(const FInputActionValue& InputValue);
	void MoveReleased(const FInputActionValue& InputValue);

	void LookTriggered(const FInputActionValue& InputValue);
	void LookReleased(const FInputActionValue& InputValue);

	void InteractStarted(const FInputActionValue& InputValue);

	void SprintTriggered(const FInputActionValue& InputValue);
	void SprintReleased(const FInputActionValue& InputValue);

	void SitDownStarted(const FInputActionValue& InputValue);

	void FlashStarted(const FInputActionValue& InputValue);

	void ZoomTriggered(const FInputActionValue& InputValue);
	void ZoomReleased(const FInputActionValue& InputValue);

	void ReportStarted(const FInputActionValue& InputValue);

	void EscapeStarted(const FInputActionValue& InputValue);

	void EnterStarted(const FInputActionValue& InputValue);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* IMCDefault;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IAMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IALook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IAInteract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IASprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IASitDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IAFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IAZoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IAReport;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IAEscape;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IAEnter;

#pragma endregion

#pragma region SitDown

protected:
	FTimerHandle SitDownCoolDownHandle;

	float SidDownCoolDown = 1.f;
	bool bCanSitDown = true;

	void SitDownTimer();
	void SitDownButtonTrue();

#pragma endregion

#pragma region UI

public:
	UFUNCTION()
	void CloseReportUI();

	void ResetReportUI();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UHSReportBaseWidget> ReportUIClass;

	UPROPERTY()
	class UHSReportBaseWidget* ReportWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UHSPauseWidget> PauseUIClass;

	UPROPERTY()
	class UHSPauseWidget* PauseWidget;

#pragma endregion

};