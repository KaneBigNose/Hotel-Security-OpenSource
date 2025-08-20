// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_CalculateDistance.generated.h"

UCLASS()
class HOTEL_SECURITY_API UBTS_CalculateDistance : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTS_CalculateDistance();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};