// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "HSFindPlayer.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSFindPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UHSFindPlayer();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	class AHSPlayer* HSPlayer;
	class UBlackboardComponent* MonsterBBComponent;

	FTimerHandle RememberHandle;
	FTimerHandle FindHandle;

	bool bCanFind = true;

	void CanFind();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MonsterRememberTime = 10.f;

	bool bForgetting = false;

	void ForgetPlayer();
};