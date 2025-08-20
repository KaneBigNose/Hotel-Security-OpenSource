// Made by LSH

#include "AI/Controller/HSAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#pragma region Base

AHSAIController::AHSAIController()
{
	PrimaryActorTick.bCanEverTick = false;

	HSAIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("HSAIPerception"));

	HSSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("HSSightConfig"));
	HSSightConfig->SightRadius = HSSightRadius;
	HSSightConfig->LoseSightRadius = HSLoseSightRadius;
	HSSightConfig->PeripheralVisionAngleDegrees = HSPeripheralVisionAngleDegrees;
	HSSightConfig->SetMaxAge(HSSightMaxAge);
	HSSightConfig->DetectionByAffiliation.bDetectEnemies = true;
	HSSightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HSSightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	HSAIPerception->ConfigureSense(*HSSightConfig);

	HSHearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HSHearingConfig"));
	HSHearingConfig->HearingRange = HSHearingRange;
	HSHearingConfig->SetMaxAge(HSHearingMaxAge);
	HSHearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HSHearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HSHearingConfig->DetectionByAffiliation.bDetectFriendlies = true;

	HSAIPerception->ConfigureSense(*HSHearingConfig);

	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComponent"));
}

void AHSAIController::BeginPlay()
{
	Super::BeginPlay();

	UBlackboardComponent* BBC = BBComponent.Get();
	UseBlackboard(BB, BBC);

	RunBehaviorTree(BT);

	SetPerceptionComponent(*HSAIPerception);
}

#pragma endregion