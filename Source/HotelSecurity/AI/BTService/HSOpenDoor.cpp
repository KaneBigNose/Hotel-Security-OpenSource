// Made by LSH

#include "AI/BTService/HSOpenDoor.h"
#include "AI/HSMonsterBase/HSMonsterBase.h"
#include "AIController.h"
#include "Interact/Door/HSInteractDoor.h"

UHSOpenDoor::UHSOpenDoor()
{
	NodeName = TEXT("Open Door");

	Interval = 0.1;

	RandomDeviation = 0.f;
}

void UHSOpenDoor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AHSMonsterBase* Monster = Cast<AHSMonsterBase>(OwnerComp.GetAIOwner()->GetCharacter());
	TArray<AHSInteractDoor*> InRangeObjects = Monster->GetInInteractRangeDoors();

	for (auto& CheckObject : InRangeObjects)
	{
		if (!CheckObject->DoorIsRotated())
		{
			CheckObject->PlayerInteractThisObject();
		}
	}
}