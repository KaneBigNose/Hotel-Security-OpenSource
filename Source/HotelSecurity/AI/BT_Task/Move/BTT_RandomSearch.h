// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_RandomSearch.generated.h"

UCLASS()
class HOTEL_SECURITY_API UBTT_RandomSearch : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTT_RandomSearch();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere)
	float SearchRadius = 10000.f;
};