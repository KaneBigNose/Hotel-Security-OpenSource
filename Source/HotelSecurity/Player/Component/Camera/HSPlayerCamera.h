// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HSPlayerCamera.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOTEL_SECURITY_API UHSPlayerCamera : public UActorComponent
{
	GENERATED_BODY()

#pragma region Base

public:
	UHSPlayerCamera();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UPROPERTY()
	class AHSPlayer* HSPlayer;

#pragma endregion

#pragma region Camera

public:
	class USpringArmComponent* GetSpringArm() { return SpringArm; }
	class UCameraComponent* GetCamera() { return Camera; }

protected:
	UFUNCTION()
	void SetCameraDieView(class AMonster_Base* Attacker);

	void RotateToAttacker(class AMonster_Base* Attacker);

protected:
	FTimerHandle RotateHandle;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCameraComponent> Camera;

#pragma endregion

};