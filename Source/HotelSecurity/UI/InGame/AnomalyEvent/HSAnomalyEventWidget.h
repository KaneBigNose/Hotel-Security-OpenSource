// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HSAnomalyEventWidget.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSAnomalyEventWidget : public UUserWidget
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY()
	class UHSGameInstance* GameInstance;

	UPROPERTY()
	class UHSWorldSubsystem* Subsystem;

#pragma endregion

#pragma region Widget

public:
	UFUNCTION(BlueprintCallable)
	void OccurAnomalyEvent();

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* AnomalyEventImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentText;

protected:
	FTimerHandle AnomalyEventHandle;

	void AnomalyEventUIClear();

	float AnomalyUIDuration = 2.5f;

#pragma endregion

};