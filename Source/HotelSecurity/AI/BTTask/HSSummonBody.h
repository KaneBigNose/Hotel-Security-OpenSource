// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HSSummonBody.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSSummonBody : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UHSSummonBody();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};