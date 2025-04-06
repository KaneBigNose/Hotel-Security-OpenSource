// Made by LSH

#include "AI/BTTask/HSSummonBody.h"
#include "AI/HSMiner/HSMiner.h"
#include "AI/AIController/HSAIController.h"

UHSSummonBody::UHSSummonBody()
{
	NodeName = TEXT("Sommon Body");
}

EBTNodeResult::Type UHSSummonBody::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AHSMiner* Miner = Cast<AHSMiner>(OwnerComp.GetAIOwner()->GetCharacter());

	if (!Miner)
	{
		return EBTNodeResult::Failed;
	}

	Miner->SummonHangingBody();

	return EBTNodeResult::Succeeded;
}