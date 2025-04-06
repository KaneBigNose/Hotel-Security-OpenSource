// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "HSOpenDoor.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSOpenDoor : public UBTService
{
	GENERATED_BODY()
	
public:
	UHSOpenDoor();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};