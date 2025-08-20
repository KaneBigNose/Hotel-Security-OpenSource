// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "UI_Button_Base.generated.h"

UCLASS(Meta = (DisableNativeTick))
class HOTEL_SECURITY_API UUI_Button_Base : public UButton
{
	GENERATED_BODY()

#pragma region Setting

public:
	void SetOwnerThisButton(class UUI_Base* Owner);

protected:
	UPROPERTY()
	TObjectPtr<class UUI_Base> WidgetOwner;

#pragma endregion

};