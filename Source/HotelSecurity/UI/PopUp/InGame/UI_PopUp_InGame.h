// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/UI_PopUp_Base.h"
#include "UI_PopUp_InGame.generated.h"

UCLASS()
class HOTEL_SECURITY_API UUI_PopUp_InGame : public UUI_PopUp_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeConstruct() override;

#pragma endregion

#pragma region Input

protected:
	virtual void InputWidget_ESC() override;

#pragma endregion

};