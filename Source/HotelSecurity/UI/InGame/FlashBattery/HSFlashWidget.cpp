// Made by LSH

#include "UI/InGame/FlashBattery/HSFlashWidget.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "Kismet/GameplayStatics.h"

void UHSFlashWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UHSFlashWidget::CheckFlashBattery(float FlashBatteryPercentage)
{
	FSlateBrush Brush;

	if (FlashBatteryPercentage <= 100 && FlashBatteryPercentage > 75)
	{
		Brush.SetResourceObject(BatteryGreenTexture);
	}
	else if (FlashBatteryPercentage <= 75 && FlashBatteryPercentage > 50)
	{
		Brush.SetResourceObject(BatteryYellowTexture);
	}
	else if (FlashBatteryPercentage <= 50 && FlashBatteryPercentage > 25)
	{
		Brush.SetResourceObject(BatteryOrangeTexture);
	}
	else if (FlashBatteryPercentage <= 25 && FlashBatteryPercentage > 0)
	{
		Brush.SetResourceObject(BatteryRedTexture);
	}
	else if (FlashBatteryPercentage <= 0)
	{
		Brush.SetResourceObject(BatteryEmptyTexture);
	}

	FlashBatteryImage->SetBrush(Brush);
}