// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_FindFlash.generated.h"

UCLASS()
class HOTEL_SECURITY_API UBTS_FindFlash : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTS_FindFlash();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY()
	TObjectPtr<class AHSPlayer> HSPlayer;

	UPROPERTY()
	TObjectPtr<class UHSAbilitySystemComponent> ASC;
};