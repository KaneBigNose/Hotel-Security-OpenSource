// Made by LSH

#include "AI/BT_Task/Action/BTT_LockDoor.h"
#include "AI/Character/HotelManager/HotelManager.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interact/Door/HSInteractDoor.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/GameplayTag/HSGameplayTags.h"

UBTT_LockDoor::UBTT_LockDoor()
{
	NodeName = TEXT("Lock Door");
}

EBTNodeResult::Type UBTT_LockDoor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AHotelManager* Owner = Cast<AHotelManager>(OwnerComp.GetAIOwner()->GetCharacter());
	UHSAbilitySystemComponent* ASC = Cast<UHSAbilitySystemComponent>(Owner->GetAbilitySystemComponent());
	UBlackboardComponent* OwnerBB = OwnerComp.GetBlackboardComponent();
	AHSInteractDoor* TargetDoor = Cast<AHSInteractDoor>(OwnerBB->GetValueAsObject(BlackboardKey.SelectedKeyName));

	ASC->CancelAbilitiesByTag(HSGameplayTags::State::Run);
	OwnerBB->SetValueAsObject(BlackboardKey.SelectedKeyName, nullptr);

	if (TargetDoor->bIsRotating)
	{
		TargetDoor->InteractThisObject();

		int32 RandomInt = FMath::RandRange(1, 4);
		if (RandomInt == 1)
		{
			TargetDoor->SetDoorLock();
		}
	}

	return EBTNodeResult::Succeeded;
}