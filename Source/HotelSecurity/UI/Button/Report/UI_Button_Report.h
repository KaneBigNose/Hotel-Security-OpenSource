// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/Button/UI_Button_Base.h"
#include "UI_Button_Report.generated.h"

UCLASS(Meta = (DisableNativeTick))
class HOTEL_SECURITY_API UUI_Button_Report : public UUI_Button_Base
{
	GENERATED_BODY()

#pragma region Base

public:
	UUI_Button_Report();

#pragma endregion

#pragma region Click

protected:
	UFUNCTION()
	virtual void SetSelectedText();

	UFUNCTION()
	void CaptureObject();

public:
	FString PlaceValue;
	FString ObjectValue;
	FString AnomalyValue;

	int32 ButtonIndex;
	int32 ObjectIndex;

#pragma endregion

};