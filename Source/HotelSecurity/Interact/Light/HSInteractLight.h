// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Interact/HSInteractObjectBase.h"
#include "HSInteractLight.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSInteractLight : public AHSInteractObjectBase
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AHSInteractLight(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Interact

public:
	virtual void InteractThisObject() override;

#pragma endregion

#pragma region Light

public:
	bool IsLightTurnOn() { return !bIsInteracted; }

protected:
	UPROPERTY(EditAnywhere, Category = "Interact")
	TObjectPtr<class UPointLightComponent> PointLight;

#pragma endregion

};