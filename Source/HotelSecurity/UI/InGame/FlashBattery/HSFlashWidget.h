// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HSFlashWidget.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSFlashWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Base

public:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Image

public:
	void CheckFlashBattery(float FlashBatteryPercentage);

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* FlashBatteryImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* BatteryGreenTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* BatteryYellowTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* BatteryOrangeTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* BatteryRedTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* BatteryEmptyTexture;

#pragma endregion

};