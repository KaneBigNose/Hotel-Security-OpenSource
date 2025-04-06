// Made by LSH

#include "AI/BTTask/HSRandomTeleport.h"
#include "AI/HSMonsterBase/HSMonsterBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "NavigationSystem.h"
#include "AI/AIController/HSAIController.h"

UHSRandomTeleport::UHSRandomTeleport()
{
	NodeName = TEXT("Random Teleport");
}

EBTNodeResult::Type UHSRandomTeleport::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	HSMonster = Cast<AHSMonsterBase>(OwnerComp.GetAIOwner()->GetCharacter());
	AHSAIController* HSMonsterController = Cast<AHSAIController>(HSMonster->GetController());
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (!HSMonster || !HSMonsterController || !NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	NavSystem->GetRandomReachablePointInRadius(HSMonster->GetActorLocation(), TeleportRadius, OUT TeleportLocation);

	HSMonster->PlayAnimMontage(TeleportStart);

	GetWorld()->GetTimerManager().SetTimer(TeleportHandle, this, &ThisClass::Teleporting, TeleportDuration, false);

	return EBTNodeResult::Succeeded;
}

void UHSRandomTeleport::Teleporting()
{
	TeleportLocation.Location.Z += 100.f;
	HSMonster->SetActorLocation(TeleportLocation.Location);
	HSMonster->PlayAnimMontage(TeleportEnd);
}