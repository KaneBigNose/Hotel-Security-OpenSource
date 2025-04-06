// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HSFrameWidget.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSFrameWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

protected:
	class UGameUserSettings* SettingHandle;

#pragma endregion

#pragma region Click

public:
	UFUNCTION()
	void Click60Button();

	UFUNCTION()
	void Click120Button();

	UFUNCTION()
	void Click144Button();

	UFUNCTION()
	void Click240Button();

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* F60Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* F120Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* F144Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* F240Button;

#pragma endregion

};