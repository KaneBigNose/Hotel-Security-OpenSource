// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_TargetDoor.generated.h"

UCLASS()
class HOTEL_SECURITY_API UBTS_TargetDoor : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTS_TargetDoor();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY()
	TObjectPtr<class AHotelManager> Owner;

	UPROPERTY()
	TObjectPtr<class UHSAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<class UBlackboardComponent> OwnerBB;
};