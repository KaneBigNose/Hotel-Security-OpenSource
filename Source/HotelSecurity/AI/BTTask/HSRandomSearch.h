// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "HSRandomSearch.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSRandomSearch : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UHSRandomSearch();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SearchRadius = 10000.f;
};