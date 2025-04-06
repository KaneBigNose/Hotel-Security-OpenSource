// Made by LSH

#include "AI/BTService/HSTurnOffLight.h"
#include "AI/HSBlackVeil/HSBlackVeil.h"
#include "AIController.h"
#include "Interact/Light/HSInteractLight.h"

UHSTurnOffLight::UHSTurnOffLight()
{
	NodeName = TEXT("Turn Off Light");

	Interval = 0.1;

	RandomDeviation = 0.f;
}

void UHSTurnOffLight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AHSBlackVeil* Monster = Cast<AHSBlackVeil>(OwnerComp.GetAIOwner()->GetCharacter());
	TArray<AHSInteractLight*> InRangeObjects = Monster->GetInInteractRangeLights();

	for (auto& CheckObject : InRangeObjects)
	{
		if (CheckObject->LightIsTurned())
		{
			CheckObject->PlayerInteractThisObject();
		}
	}
}