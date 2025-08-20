// Made by LSH

#include "AI/BT_Task/Setting/BTT_TargetSetting.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/Character/HSPlayer.h"
#include "Kismet/GameplayStatics.h"

UBTT_TargetSetting::UBTT_TargetSetting()
{
	NodeName = TEXT("Target Setting");
}

EBTNodeResult::Type UBTT_TargetSetting::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AHSPlayer* HSPlayer = Cast<AHSPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!HSPlayer)
	{
		return EBTNodeResult::Failed;
	}

	if (bIsTargetOn)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, HSPlayer);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, nullptr);
	}

	return EBTNodeResult::Succeeded;
}