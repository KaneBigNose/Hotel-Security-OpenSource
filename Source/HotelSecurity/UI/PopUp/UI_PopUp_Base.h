// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/UI_Base.h"
#include "UI_PopUp_Base.generated.h"

UCLASS(Abstract, Meta = (DisableNativeTick))
class HOTEL_SECURITY_API UUI_PopUp_Base : public UUI_Base
{
	GENERATED_BODY()

#pragma region Base

public:
	UUI_PopUp_Base(const FObjectInitializer& ObjectInitializer);

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

#pragma endregion

#pragma region Highlight

protected:
	virtual void InitButtons() PURE_VIRTUAL(UUI_PopUp_Base::InitButtons, );

public:
	virtual void Highlight(TArray<class UButton*> Buttons, int32 TargetIndex);

#pragma endregion

#pragma region Input

protected:
	UFUNCTION()
	virtual void InputWidget_Enter() PURE_VIRTUAL(UUI_PopUp_Base::InputWidget_Enter, );

	UFUNCTION()
	virtual void InputWidget_ESC() PURE_VIRTUAL(UUI_PopUp_Base::InputWidget_ESC, );

#pragma endregion

};