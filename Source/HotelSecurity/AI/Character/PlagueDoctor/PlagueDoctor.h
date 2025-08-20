// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/Character/Monster_Base.h"
#include "PlagueDoctor.generated.h"

UCLASS()
class HOTEL_SECURITY_API APlagueDoctor : public AMonster_Base
{
	GENERATED_BODY()

#pragma region Base

public:
	APlagueDoctor(const FObjectInitializer& ObjectInitializer);

#pragma endregion

};