// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HSAimWidget.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSAimWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	void ChangeInteractAim(bool bCanInteract);

protected:
	UPROPERTY()
	class UCanvasPanelSlot* AimWidgetCanvasSlot;

	UPROPERTY(meta = (BindWidget))
	class UImage* AimImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* NormalTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* InteractTexture;
};