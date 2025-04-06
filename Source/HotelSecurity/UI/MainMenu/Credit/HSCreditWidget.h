// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Interface/HSUIInterface.h"
#include "HSCreditWidget.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSCreditWidget : public UUserWidget, public IHSUIInterface
{
	GENERATED_BODY()

#pragma region Interface

public:
	virtual void EscapeCurrentWidget() override;
	virtual void EnterCurrentWidget() override;

#pragma endregion

};