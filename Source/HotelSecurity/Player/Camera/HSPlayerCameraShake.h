// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShakeBase.h"
#include "HSPlayerCameraShake.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSPlayerCameraShake : public UCameraShakeBase
{
	GENERATED_BODY()
	
public:
	UHSPlayerCameraShake(const FObjectInitializer& ObjectInitializer);
};