// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/Character/Monster_Base.h"
#include "BellyMan.generated.h"

UCLASS()
class HOTEL_SECURITY_API ABellyMan : public AMonster_Base
{
	GENERATED_BODY()
	
#pragma region Base

public:
	ABellyMan(const FObjectInitializer& ObjectInitializer);

#pragma endregion

};