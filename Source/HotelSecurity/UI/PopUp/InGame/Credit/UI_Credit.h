// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/InGame/UI_PopUp_InGame.h"
#include "UI_Credit.generated.h"

UCLASS(Meta = (DisableNativeTick))
class HOTEL_SECURITY_API UUI_Credit : public UUI_PopUp_InGame
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeConstruct() override;

#pragma endregion

#pragma region Credit

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> CreditScroll;

#pragma endregion

#pragma region Input

public:
	virtual void InputWidget_Enter() override;
	virtual void InputWidget_ESC() override;

#pragma endregion

};