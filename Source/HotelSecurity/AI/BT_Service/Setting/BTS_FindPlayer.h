// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_FindPlayer.generated.h"

UCLASS()
class HOTEL_SECURITY_API UBTS_FindPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
#pragma region Base

public:
	UBTS_FindPlayer();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY()
	TObjectPtr<class AHSCharacter> Owner;

	UPROPERTY()
	TObjectPtr<class UHSAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<class UAIPerceptionComponent> OwnerPerception;

	UPROPERTY()
	TObjectPtr<class UBlackboardComponent> OwnerBB;

#pragma endregion

#pragma region Find Player

protected:
	void FindPlayer(AActor* CheckActor);

protected:
	bool bCanFind = true;

#pragma endregion

};