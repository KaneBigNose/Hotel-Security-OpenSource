// Made by LSH

#include "AI/BT_Task/Setting/BTT_TagManagement.h"
#include "AI/Character/Monster_Base.h"
#include "AI/Controller/HSAIController.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"

UBTT_TagManagement::UBTT_TagManagement()
{
	NodeName = TEXT("Tag Management");
}

EBTNodeResult::Type UBTT_TagManagement::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonster_Base* Owner = Cast<AMonster_Base>(OwnerComp.GetAIOwner()->GetCharacter());
	auto* ASC = Cast<UHSAbilitySystemComponent>(Owner->GetAbilitySystemComponent());

	if (bIsAdd)
	{
		ASC->AddUniqueGameplayTag(TagValue);
	}
	else
	{
		ASC->RemoveLooseGameplayTag(TagValue);
	}

	return EBTNodeResult::Succeeded;
}