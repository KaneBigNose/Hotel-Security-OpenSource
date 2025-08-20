// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/MainMenu/UI_PopUp_MainMenu.h"
#include "UI_Credit.generated.h"

UCLASS(Meta = (DisableNativeTick))
class HOTEL_SECURITY_API UUI_Credit : public UUI_PopUp_MainMenu
{
	GENERATED_BODY()

#pragma region Input

public:
	virtual void InputWidget_Enter() override;

#pragma endregion

};