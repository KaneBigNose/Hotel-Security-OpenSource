// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Interface/HSUIInterface.h"
#include "HSSettingWidget.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSSettingWidget : public UUserWidget, public IHSUIInterface
{
	GENERATED_BODY()

#pragma region Interface

public:
	virtual void EscapeCurrentWidget() override;
	virtual void EnterCurrentWidget() override;

#pragma endregion

};