// Made by LSH

#include "AI/BT_Service/Setting/BTS_FindPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/Character/HSPlayer.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "GAS/AbilitySystemComponent/HSAbilitySystemComponent.h"
#include "GAS/GameplayTag/HSGameplayTags.h"

#pragma region Base

UBTS_FindPlayer::UBTS_FindPlayer()
{
	NodeName = TEXT("Find Player");

	Interval = 0.1f;

	RandomDeviation = 0;
}

void UBTS_FindPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bCanFind)
	{
		return;
	}

	if (!Owner)
	{
		Owner = Cast<AHSCharacter>(OwnerComp.GetAIOwner()->GetCharacter());
		ASC = Cast<UHSAbilitySystemComponent>(Owner->GetAbilitySystemComponent());
		OwnerPerception = Cast<UAIPerceptionComponent>(OwnerComp.GetAIOwner()->GetPerceptionComponent());
		OwnerBB = OwnerComp.GetBlackboardComponent();
	}

	TArray<AActor*> SightedActors;
	TArray<AActor*> HeardActors;
	OwnerPerception->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), SightedActors);
	OwnerPerception->GetCurrentlyPerceivedActors(UAISense_Hearing::StaticClass(), HeardActors);

	for (auto CheckActor : SightedActors)
	{
		if (CheckActor->IsA(AHSPlayer::StaticClass()))
		{
			FindPlayer(CheckActor);
			return;
		}
	}

	for (auto CheckActor : HeardActors)
	{
		if (CheckActor->IsA(AHSPlayer::StaticClass()))
		{
			FindPlayer(CheckActor);
			return;
		}
	}
}

#pragma endregion

#pragma region Find Player

void UBTS_FindPlayer::FindPlayer(AActor* CheckActor)
{
	if (!Owner)
	{
		return;
	}

	bCanFind = false;

	ASC->CancelAbilitiesByTag(HSGameplayTags::State::Run);
	ASC->ActiveAbilitiesByTag(HSGameplayTags::State::Run);
	OwnerBB->SetValueAsObject(BlackboardKey.SelectedKeyName, CheckActor);

	auto* TargetASC = Cast<UHSAbilitySystemComponent>(Cast<AHSCharacter>(CheckActor)->GetAbilitySystemComponent());
	TargetASC->ExecuteGameplayCue(HSGameplayTags::GameplayCue::Camera::Shake_Default);
	TargetASC->ExecuteGameplayCue(HSGameplayTags::GameplayCue::Sound::Chased);
	TargetASC->AddUniqueGameplayTag(HSGameplayTags::State::Chased);

	FTimerHandle FindHandle;
	GetWorld()->GetTimerManager().SetTimer(FindHandle, [this, TargetASC]()
		{
			bCanFind = true;
			ASC->CancelAbilitiesByTag(HSGameplayTags::State::Run);
			OwnerBB->SetValueAsObject(BlackboardKey.SelectedKeyName, nullptr);
			TargetASC->RemoveLooseGameplayTag(HSGameplayTags::State::Chased);
		}, 20, false);
}

#pragma endregion