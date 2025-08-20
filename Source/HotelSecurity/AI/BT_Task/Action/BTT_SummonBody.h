// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_SummonBody.generated.h"

UCLASS()
class HOTEL_SECURITY_API UBTT_SummonBody : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_SummonBody();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};