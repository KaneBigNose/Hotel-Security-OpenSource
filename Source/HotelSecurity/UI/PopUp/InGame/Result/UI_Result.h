// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/InGame/UI_PopUp_InGame.h"
#include "UI_Result.generated.h"

UCLASS()
class HOTEL_SECURITY_API UUI_Result : public UUI_PopUp_InGame
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(FGeometry const& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY()
	TObjectPtr<class AHSPlayer> HSPlayer;

	UPROPERTY()
	TObjectPtr<class UHSAbilitySystemComponent> ASC;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ResultText;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundWave> ResultSound;

#pragma endregion

#pragma region Report

public:
	void ShowReportResultImage(bool bSuccessed);

#pragma endregion

#pragma region Input

protected:
	virtual void InputWidget_ESC() override;

#pragma endregion

};