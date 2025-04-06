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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|BT")
	class UBlackboardData* HSBlackboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|BT")
	class UBlackboardComponent* HSBlackboardComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|BT")
	class UBehaviorTree* HSBehaviorTree;

#pragma endregion

#pragma region Perception

public:
	class UAIPerceptionComponent* GetHSAIPerception() { return HSAIPerception; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAIPerceptionComponent* HSAIPerception;

	class UAISenseConfig_Sight* HSSightConfig;
	class UAISenseConfig_Hearing* HSHearingConfig;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|Perception|Sight")
	float HSSightRadius = 3000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|Perception|Sight")
	float HSLoseSightRadius = 3500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|Perception|Sight")
	float HSPeripheralVisionAngleDegrees = 80.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|Perception|Sight")
	float HSSightMaxAge = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|Perception|Hearing")
	float HSHearingRange = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|Perception|Hearing")
	float HSHearingMaxAge = 5.f;

#pragma endregion

};