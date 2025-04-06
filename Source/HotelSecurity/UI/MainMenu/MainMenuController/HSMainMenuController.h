// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HSMainMenuController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

UCLASS()
class HOTEL_SECURITY_API AHSMainMenuController : public APlayerController
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

protected:
	class UHSGameInstance* GameInstance;

#pragma endregion

#pragma region Input

protected:
	void EnterStarted(const FInputActionValue& InputValue);

	void EscapeStarted(const FInputActionValue& InputValue);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* IMC_UI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IAEnter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IAEscape;

#pragma endregion

};