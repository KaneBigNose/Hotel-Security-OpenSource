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
	AHSInteractLight();

#pragma endregion

#pragma region Interact

public:
	virtual void PlayerInteractThisObject() override;

#pragma endregion

#pragma region Light

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	class UPointLightComponent* PointLight;

public:
	bool LightIsTurned() { return !bIsInteracted; }

#pragma endregion

};