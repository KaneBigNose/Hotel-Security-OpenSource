// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Interface/HSUIInterface.h"
#include "HSMapSelectWidget.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSMapSelectWidget : public UUserWidget, public IHSUIInterface
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

protected:
	class UHSGameInstance* GameInstance;

#pragma endregion

#pragma region Text

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HotelMap;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MineMap;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HospitalMap;

#pragma endregion

#pragma region Click

public:
	UFUNCTION()
	void ClickHotelSelectButton();

	UFUNCTION()
	void ClickMineSelectButton();

	UFUNCTION()
	void ClickHospitalSelectButton();

	UFUNCTION()
	void ClickStartButton();

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* HotelSelectButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MineSelectButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* HospitalSelectButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

#pragma endregion

#pragma region Image

protected:
	void SettingPreviewImage(class UTexture2D* PreviewTexture);

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* PreviewImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* PreviewUnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* PreviewHotel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* PreviewMine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* PreviewHospital;

#pragma endregion

#pragma region Interface

public:
	virtual void EscapeCurrentWidget() override;
	virtual void EnterCurrentWidget() override;

#pragma endregion

};