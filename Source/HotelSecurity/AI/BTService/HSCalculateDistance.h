// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "HSCalculateDistance.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSCalculateDistance : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UHSCalculateDistance();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};