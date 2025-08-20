// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_TargetSetting.generated.h"

UCLASS()
class HOTEL_SECURITY_API UBTT_TargetSetting : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTT_TargetSetting();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere)
	bool bIsTargetOn = true;
};