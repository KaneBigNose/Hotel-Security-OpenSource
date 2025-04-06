// Made by LSH

#include "AI/BTTask/HSRandomSearch.h"
#include "AI/HSMonsterBase/HSMonsterBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "NavigationSystem.h"
#include "AI/AIController/HSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UHSRandomSearch::UHSRandomSearch()
{
	NodeName = TEXT("Random Search");
}

EBTNodeResult::Type UHSRandomSearch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AHSMonsterBase* HSMonster = Cast<AHSMonsterBase>(OwnerComp.GetAIOwner()->GetCharacter());
	AHSAIController* HSMonsterController = Cast<AHSAIController>(HSMonster->GetController());
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (!HSMonster || !HSMonsterController || !NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation RandomLocation;
	NavSystem->GetRandomReachablePointInRadius(HSMonster->GetActorLocation(), SearchRadius, OUT RandomLocation);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, RandomLocation);

	return EBTNodeResult::Succeeded;
}