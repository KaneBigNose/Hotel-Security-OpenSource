// Made by LSH

#include "AI/BT_Service/Setting/BTS_TargetDoor.h"
#include "AI/Character/HotelManager/HotelManager.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interact/Door/HSInteractDoor.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/GameplayTag/HSGameplayTags.h"

UBTS_TargetDoor::UBTS_TargetDoor()
{
	NodeName = TEXT("Target Door");

	Interval = 0.1f;

	RandomDeviation = 0;
}

void UBTS_TargetDoor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!Owner)
	{
		Owner = Cast<AHotelManager>(OwnerComp.GetAIOwner()->GetCharacter());
		ASC = Cast<UHSAbilitySystemComponent>(Owner->GetAbilitySystemComponent());
		OwnerBB = OwnerComp.GetBlackboardComponent();
	}

	if (Owner->FindDoors.IsEmpty())
	{
		return;
	}

	if (OwnerBB->GetValueAsObject(BlackboardKey.SelectedKeyName))
	{
		return;
	}

	AHSInteractDoor* TargetDoor = Cast<AHSInteractDoor>(Owner->FindDoors[0]);
	OwnerBB->SetValueAsObject(BlackboardKey.SelectedKeyName, TargetDoor);
	OwnerBB->SetValueAsVector(FName("TargetDoorLocation"), TargetDoor->GetActorLocation());
	Owner->FindDoors.Remove(TargetDoor);
	ASC->ActiveAbilitiesByTag(HSGameplayTags::State::Run);
}