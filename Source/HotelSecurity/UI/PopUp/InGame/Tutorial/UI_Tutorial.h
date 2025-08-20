// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/InGame/UI_PopUp_InGame.h"
#include "UI_Tutorial.generated.h"

UCLASS(Meta = (DisableNativeTick))
class HOTEL_SECURITY_API UUI_Tutorial : public UUI_PopUp_InGame
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY()
	TObjectPtr<class UUI_Controller> UICon;

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_PopUp_Base> PreviousClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_PopUp_Base> NextClass;

#pragma endregion

#pragma region Click

protected:
	UFUNCTION()
	void Click_Previous();

	UFUNCTION()
	void Click_Next();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> PreviousButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> NextButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> WorkButton;

#pragma endregion

#pragma region Input

public:
	virtual void InputWidget_Enter() override;

#pragma endregion

};