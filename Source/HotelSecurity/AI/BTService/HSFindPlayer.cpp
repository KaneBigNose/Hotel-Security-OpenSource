// Made by LSH

#include "AI/BTService/HSFindPlayer.h"
#include "AI/AIController/HSAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "Player/Sound/HSPlayerSound.h"
#include "Player/Camera/HSPlayerCamera.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "AI/HSMonsterBase/HSMonsterBase.h"
#include "GAS/GameplayTag/HSPlayerGameplayTags.h"
#include "Kismet/GameplayStatics.h"

UHSFindPlayer::UHSFindPlayer()
{
	NodeName = TEXT("Find Player");

	Interval = 0.5;

	RandomDeviation = 0.f;
}

void UHSFindPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AHSMonsterBase* Monster = Cast<AHSMonsterBase>(OwnerComp.GetAIOwner()->GetCharacter());
	AHSAIController* MonsterController = Cast<AHSAIController>(OwnerComp.GetAIOwner());
	UAIPerceptionComponent* MonsterPerception = Cast<UAIPerceptionComponent>(MonsterController->GetHSAIPerception());
	MonsterBBComponent = OwnerComp.GetBlackboardComponent();

	TArray<AActor*> SightedActors;
	TArray<AActor*> HeardActors;

	MonsterPerception->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), SightedActors);
	MonsterPerception->GetCurrentlyPerceivedActors(UAISense_Hearing::StaticClass(), HeardActors);

	if (SightedActors.Num() <= 0 && HeardActors.Num() <= 0)
	{
		Monster->SetNormalMode();

		HSPlayer = Cast<AHSPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		HSPlayer->GetHSPlayerStateContainer().RemoveTag(HSPlayerGameplayTags::HSPlayer_State_Chased);

		if (!bForgetting)
		{
			bForgetting = true;
			GetWorld()->GetTimerManager().SetTimer(RememberHandle, this, &UHSFindPlayer::ForgetPlayer, MonsterRememberTime, false);
		}

		return;
	}

	if (!bCanFind)
	{
		return;
	}

	for (auto CheckActor : SightedActors)
	{
		if (CheckActor->IsA(AHSPlayer::StaticClass()))
		{
			bCanFind = false;
			GetWorld()->GetTimerManager().SetTimer(FindHandle, this, &UHSFindPlayer::CanFind, 10.f, false);
			MonsterBBComponent->SetValueAsObject(BlackboardKey.SelectedKeyName, CheckActor);
			Monster->SetChaseTargetMode();
			Cast<AHSPlayer>(CheckActor)->GetHSPlayerCameraComponent()->MakeCameraShake(true);
			return;
		}
	}

	for (auto CheckActor : HeardActors)
	{
		if (CheckActor->IsA(AHSPlayer::StaticClass()))
		{
			bCanFind = false;
			GetWorld()->GetTimerManager().SetTimer(FindHandle, this, &UHSFindPlayer::CanFind, 10.f, false);
			MonsterBBComponent->SetValueAsObject(BlackboardKey.SelectedKeyName, CheckActor);
			Monster->SetChaseTargetMode();
			Cast<AHSPlayer>(CheckActor)->GetHSPlayerCameraComponent()->MakeCameraShake(true);
			return;
		}
	}
}

void UHSFindPlayer::CanFind()
{
	bCanFind = true;
}

void UHSFindPlayer::ForgetPlayer()
{
	HSPlayer->GetHSPlayerSoundComponent()->PlayBGM(true);
	bForgetting = false;
	MonsterBBComponent->SetValueAsObject(BlackboardKey.SelectedKeyName, nullptr);
}