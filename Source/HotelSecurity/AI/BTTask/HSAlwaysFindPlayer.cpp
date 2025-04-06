// Made by LSH

#include "AI/BTTask/HSAlwaysFindPlayer.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UHSAlwaysFindPlayer::UHSAlwaysFindPlayer()
{
	NodeName = TEXT("Always Find Player");
}

EBTNodeResult::Type UHSAlwaysFindPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AHSPlayer* HSPlayer = Cast<AHSPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!HSPlayer)
	{
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, HSPlayer);

	return EBTNodeResult::Succeeded;
}