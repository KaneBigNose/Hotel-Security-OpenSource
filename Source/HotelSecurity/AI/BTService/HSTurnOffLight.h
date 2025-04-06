// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "HSTurnOffLight.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSTurnOffLight : public UBTService
{
	GENERATED_BODY()
	
public:
	UHSTurnOffLight();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};