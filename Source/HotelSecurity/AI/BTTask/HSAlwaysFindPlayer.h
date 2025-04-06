// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "HSAlwaysFindPlayer.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSAlwaysFindPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UHSAlwaysFindPlayer();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};