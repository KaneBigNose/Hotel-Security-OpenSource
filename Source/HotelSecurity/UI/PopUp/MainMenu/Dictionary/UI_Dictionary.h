// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/InGame/Tutorial/UI_Tutorial.h"
#include "AI/Character/Monster_Base.h"
#include "UI_Dictionary.generated.h"

UCLASS(Meta = (DisableNativeTick))
class HOTEL_SECURITY_API UUI_Dictionary : public UUI_Tutorial
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeConstruct() override;

#pragma endregion

#pragma region Data

protected:
	UPROPERTY(EditAnywhere)
	EMonsterType MonsterName;

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> PreviewImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Explain;

#pragma endregion

#pragma region Input

public:
	virtual void InputWidget_ESC() override;

#pragma endregion

};