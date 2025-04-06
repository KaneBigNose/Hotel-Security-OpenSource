// Made by LSH

#include "AI/BTService/HSCalculateDistance.h"
#include "AI/HSMonsterBase/HSMonsterBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "AI/AIController/HSAIController.h"

UHSCalculateDistance::UHSCalculateDistance()
{
	NodeName = TEXT("Calculate Distance");

	Interval = 0.1;

	RandomDeviation = 0.f;
}

void UHSCalculateDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AHSMonsterBase* HSMonster = Cast<AHSMonsterBase>(OwnerComp.GetAIOwner()->GetCharacter());

	AHSPlayer* HSPlayer = Cast<AHSPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));

	if (!HSMonster || !HSPlayer)
	{
		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(FName("DeathRange"), HSMonster->GetDistanceTo(HSPlayer));
}