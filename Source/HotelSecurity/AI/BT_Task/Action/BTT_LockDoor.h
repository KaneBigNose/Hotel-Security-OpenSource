// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_LockDoor.generated.h"

UCLASS()
class HOTEL_SECURITY_API UBTT_LockDoor : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTT_LockDoor();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};