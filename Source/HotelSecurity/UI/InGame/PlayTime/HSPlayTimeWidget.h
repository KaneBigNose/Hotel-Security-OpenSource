// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HSPlayTimeWidget.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSPlayTimeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UHSPlayTimeWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayTimeTextBlock;

protected:
	UPROPERTY()
	class AHSGameMode* HSGamemode;
};