// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AT_Zooming.generated.h"

UCLASS()
class HOTEL_SECURITY_API UAT_Zooming : public UAbilityTask
{
	GENERATED_BODY()

public:
	static UAT_Zooming* CreateTask(UGameplayAbility* OwningAbility)
	{
		UAT_Zooming* Task = NewAbilityTask<UAT_Zooming>(OwningAbility);

		return Task;
	}

protected:
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

protected:
	FTimerHandle ZoomHandle;

	void Zooming(class AHSPlayer* Owner);

protected:
	float ZoomCameraArmLength = -300.f;
	float CameraSpeed = 24.f;
};