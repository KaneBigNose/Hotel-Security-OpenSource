// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI_Controller.generated.h"

#pragma region Declare

UENUM(BlueprintType)
enum class EInputModeType : uint8
{
	GameOnly	UMETA(DisplayName = "GameOnly"),
	UIOnly		UMETA(DisplayName = "UIOnly"),
	GameAndUI	UMETA(DisplayName = "GameAndUI")
};

#pragma endregion

UCLASS()
class HOTEL_SECURITY_API UUI_Controller : public UGameInstanceSubsystem
{
	GENERATED_BODY()

#pragma region Widget

public:
	class UUI_Base* OpenBaseWidget(TSubclassOf<class UUI_Base> WidgetClass, const EInputModeType& InputModeType);
	class UUI_PopUp_Base* OpenPopUpWidget(TSubclassOf<class UUI_PopUp_Base> WidgetClass);
	class UUI_PopUp_Base* OpenStrongPopUpWidget(TSubclassOf<class UUI_PopUp_Base> WidgetClass);

	void CloseBaseWidget();
	void ClosePopUpWidget(const EInputModeType& InputModeType);
	void CloseStrongPopUpWidget(const EInputModeType& InputModeType);

	class UUI_Base* GetCurrentBaseWidget() { return BaseWidget; }
	class UUI_PopUp_Base* GetCurrentPopUpWidget() { return PopUpWidget; }

protected:
	void SetInputMode(const EInputModeType& InputModeType);

protected:
	UPROPERTY()
	TObjectPtr<class UUI_Base> BaseWidget;

	UPROPERTY()
	TObjectPtr<class UUI_PopUp_Base> PopUpWidget;

	int32 ZOrderIndex = 0;

#pragma endregion

};