// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/MainMenu/UI_PopUp_MainMenu.h"
#include "UI_Loading.generated.h"

UCLASS()
class HOTEL_SECURITY_API UUI_Loading : public UUI_PopUp_MainMenu
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_PopUp_Base> TutorialClass;

#pragma endregion

#pragma region Animation

protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Disappear;

	float CurrentTime = 0;
	const float MaxTime = 3.5f;

#pragma endregion

#pragma region Input

protected:
	virtual void InputWidget_ESC() override;

#pragma endregion

};