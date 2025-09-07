// Made by LSH

#include "AI/BT_Service/Setting/BTS_FindFlash.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Character/HSPlayer.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/GameplayTag/HSGameplayTags.h"

UBTS_FindFlash::UBTS_FindFlash()
{
	NodeName = TEXT("Find Flash");

	Interval = 0.1f;

	RandomDeviation = 0;
}

void UBTS_FindFlash::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!HSPlayer)
	{
		HSPlayer = Cast<AHSPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		ASC = Cast<UHSAbilitySystemComponent>(HSPlayer->GetAbilitySystemComponent());
	}

	if (ASC->HasMatchingGameplayTag(HSGameplayTags::Action::Flash))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, HSPlayer->GetActorLocation());
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("RandomMove"), false);

		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("RandomMove"), true);
}