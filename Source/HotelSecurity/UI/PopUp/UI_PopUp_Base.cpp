// Made by LSH

#include "UI/PopUp/UI_PopUp_Base.h"
#include "Components/Button.h"

#pragma region Base

UUI_PopUp_Base::UUI_PopUp_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bIsFocusable = true;
}

FReply UUI_PopUp_Base::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return FReply::Handled();
}

FReply UUI_PopUp_Base::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	const FKey Key = InKeyEvent.GetKey();

	if (Key == EKeys::Enter)
	{
		InputWidget_Enter();
		return FReply::Handled();
	}
	else if (Key == EKeys::Escape)
	{
		InputWidget_ESC();
		return FReply::Handled();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

#pragma endregion

#pragma region Highlight

void UUI_PopUp_Base::Highlight(TArray<UButton*> Buttons, int32 TargetIndex)
{
	for (int32 Index = 0; Index < Buttons.Num(); Index++)
	{
		FButtonStyle ButtonStyle = Buttons[Index]->WidgetStyle;
		ButtonStyle.Normal.TintColor = FSlateColor(FLinearColor(1, 1, 1, 0));

		if (Index == TargetIndex)
		{
			ButtonStyle.Normal.TintColor = FSlateColor(FLinearColor(1, 1, 1, 0.5f));
		}

		Buttons[Index]->SetStyle(ButtonStyle);
	}
}

#pragma endregion