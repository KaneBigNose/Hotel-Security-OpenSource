// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HSAIController.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSAIController : public AAIController
{
	GENERATED_BODY()

#pragma region Base

public:
	AHSAIController();

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region BT & BB

protected:
	UPROPERTY(EditAnywhere, Category = "Setting|BB")
	TObjectPtr<class UBlackboardData> BB;

	UPROPERTY()
	TObjectPtr<class UBlackboardComponent> BBComponent;

	UPROPERTY(EditAnywhere, Category = "Setting|BT")
	TObjectPtr<class UBehaviorTree> BT;

#pragma endregion

#pragma region Perception

public:
	class UAIPerceptionComponent* GetHSAIPerception() { return HSAIPerception; }

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAIPerceptionComponent> HSAIPerception;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAISenseConfig_Sight> HSSightConfig;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAISenseConfig_Hearing> HSHearingConfig;

protected:
	UPROPERTY(EditAnywhere, Category = "Setting|Perception|Sight")
	float HSSightRadius = 3000.f;

	UPROPERTY(EditAnywhere, Category = "Setting|Perception|Sight")
	float HSLoseSightRadius = 3500.f;

	UPROPERTY(EditAnywhere, Category = "Setting|Perception|Sight")
	float HSPeripheralVisionAngleDegrees = 80.f;

	UPROPERTY(EditAnywhere, Category = "Setting|Perception|Sight")
	float HSSightMaxAge = 5.f;

	UPROPERTY(EditAnywhere, Category = "Setting|Perception|Hearing")
	float HSHearingRange = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Setting|Perception|Hearing")
	float HSHearingMaxAge = 5.f;

#pragma endregion

};