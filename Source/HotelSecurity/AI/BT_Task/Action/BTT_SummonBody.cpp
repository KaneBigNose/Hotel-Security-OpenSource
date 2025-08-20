// Made by LSH

#include "AI/BT_Task/Action/BTT_SummonBody.h"
#include "AI/Character/Miner/Miner.h"
#include "AI/Controller/HSAIController.h"

UBTT_SummonBody::UBTT_SummonBody()
{
	NodeName = TEXT("Sommon Body");
}

EBTNodeResult::Type UBTT_SummonBody::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMiner* Miner = Cast<AMiner>(OwnerComp.GetAIOwner()->GetCharacter());

	Miner->SummonHangingBody();

	return EBTNodeResult::Succeeded;
}