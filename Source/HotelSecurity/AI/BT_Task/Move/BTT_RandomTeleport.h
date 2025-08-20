// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_RandomTeleport.generated.h"

UCLASS()
class HOTEL_SECURITY_API UBTT_RandomTeleport : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_RandomTeleport();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	void Teleporting(class UBehaviorTreeComponent& BT, class AMonster_Base* Owner, struct FNavLocation TeleportLocation);

protected:
	UPROPERTY(EditAnywhere)
	float TeleportRadius = 2000.f;

	UPROPERTY(EditAnywhere)
	float TeleportDuration = 3.f;
};