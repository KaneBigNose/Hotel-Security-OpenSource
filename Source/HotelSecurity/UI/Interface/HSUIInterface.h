// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HSUIInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHSUIInterface : public UInterface
{
	GENERATED_BODY()
};

class HOTEL_SECURITY_API IHSUIInterface
{
	GENERATED_BODY()

public:
	virtual void EscapeCurrentWidget() = 0;
	virtual void EnterCurrentWidget() = 0;
};