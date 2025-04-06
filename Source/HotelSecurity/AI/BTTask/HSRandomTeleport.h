// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HSRandomTeleport.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSRandomTeleport : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UHSRandomTeleport();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY()
	class AHSMonsterBase* HSMonster;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimMontage* TeleportStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimMontage* TeleportEnd;

	struct FNavLocation TeleportLocation;

	FTimerHandle TeleportHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TeleportDuration = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TeleportRadius = 2000.f;

	void Teleporting();
};