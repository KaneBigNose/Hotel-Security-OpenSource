// Made by LSH

#include "AI/BT_Service/Calculation/BTS_CalculateDistance.h"
#include "AI/Character/Monster_Base.h"
#include "AI/Controller/HSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/Character/HSPlayer.h"

UBTS_CalculateDistance::UBTS_CalculateDistance()
{
	NodeName = TEXT("Calculate Distance");

	Interval = 0.1f;

	RandomDeviation = 0;
}

void UBTS_CalculateDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AMonster_Base* HSMonster = Cast<AMonster_Base>(OwnerComp.GetAIOwner()->GetCharacter());
	AHSPlayer* HSPlayer = Cast<AHSPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));

	if (!HSMonster || !HSPlayer)
	{
		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(BlackboardKey.SelectedKeyName, HSMonster->GetDistanceTo(HSPlayer));
}