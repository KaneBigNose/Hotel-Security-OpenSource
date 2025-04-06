// Made by LSH

#include "UI/InGame/Aim/HSAimWidget.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Components/CanvasPanelSlot.h"

void UHSAimWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AimWidgetCanvasSlot = Cast<UCanvasPanelSlot>(Slot);
}

void UHSAimWidget::ChangeInteractAim(bool bCanInteract)
{
	if (!NormalTexture || !InteractTexture)
	{
		return;
	}

	FSlateBrush Brush;

	if (bCanInteract)
	{
		Brush.SetResourceObject(InteractTexture);
		AimWidgetCanvasSlot->SetPosition(FVector2D(-12, -12));
		AimWidgetCanvasSlot->SetSize(FVector2D(24, 24));
	}
	else
	{
		Brush.SetResourceObject(NormalTexture);
		AimWidgetCanvasSlot->SetPosition(FVector2D(-3, -3));
		AimWidgetCanvasSlot->SetSize(FVector2D(6, 6));
	}

	Brush.SetImageSize(FVector2d(100, 100));
	AimImage->SetBrush(Brush);
}