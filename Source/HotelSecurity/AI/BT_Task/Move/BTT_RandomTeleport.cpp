// Made by LSH

#include "AI/BT_Task/Move/BTT_RandomTeleport.h"
#include "AI/Character/Monster_Base.h"
#include "AI/Controller/HSAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "NavigationSystem.h"

UBTT_RandomTeleport::UBTT_RandomTeleport()
{
	NodeName = TEXT("Random Teleport");
}

EBTNodeResult::Type UBTT_RandomTeleport::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonster_Base* Owner = Cast<AMonster_Base>(OwnerComp.GetAIOwner()->GetCharacter());
	AHSAIController* OwnerController = Cast<AHSAIController>(Owner->GetController());
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (!Owner || !OwnerController || !NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation TeleportLocation;
	NavSystem->GetRandomReachablePointInRadius(Owner->GetActorLocation(), TeleportRadius, OUT TeleportLocation);

	UBehaviorTreeComponent* BTC = &OwnerComp;

	FTimerHandle TeleportHandle;
	GetWorld()->GetTimerManager().SetTimer(TeleportHandle, [this, BTC, Owner, TeleportLocation]()
		{
			Teleporting(*BTC, Owner, TeleportLocation);
		}, TeleportDuration, false);

	return EBTNodeResult::InProgress;
}

void UBTT_RandomTeleport::Teleporting(UBehaviorTreeComponent& BT, AMonster_Base* Owner, FNavLocation TeleportLocation)
{
	TeleportLocation.Location.Z += 100.f;
	Owner->SetActorLocation(TeleportLocation.Location);

	FinishLatentTask(BT, EBTNodeResult::Succeeded);
}