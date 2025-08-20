// Made by LSH

#include "AI/BT_Task/Move/BTT_RandomSearch.h"
#include "AI/Character/Monster_Base.h"
#include "AI/Controller/HSAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTT_RandomSearch::UBTT_RandomSearch()
{
	NodeName = TEXT("Random Search");
}

EBTNodeResult::Type UBTT_RandomSearch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonster_Base* Owner = Cast<AMonster_Base>(OwnerComp.GetAIOwner()->GetCharacter());
	AHSAIController* OwnerController = Cast<AHSAIController>(Owner->GetController());
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (!Owner || !OwnerController || !NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation RandomLocation;
	NavSystem->GetRandomReachablePointInRadius(Owner->GetActorLocation(), SearchRadius, OUT RandomLocation);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, RandomLocation);

	return EBTNodeResult::Succeeded;
}