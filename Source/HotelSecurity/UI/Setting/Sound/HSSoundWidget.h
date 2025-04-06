// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HSSoundWidget.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSSoundWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Click

public:
	UFUNCTION()
	void ClickSoundSlider(float SoundValue);

protected:
	UPROPERTY(meta = (BindWidget))
	class USlider* SoundSlider;

#pragma endregion

};