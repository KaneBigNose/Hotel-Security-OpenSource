// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_TagManagement.generated.h"

UCLASS()
class HOTEL_SECURITY_API UBTT_TagManagement : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTT_TagManagement();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere)
	bool bIsAdd = true;

	UPROPERTY(EditAnywhere)
	struct FGameplayTag TagValue;
};