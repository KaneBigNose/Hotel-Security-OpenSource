// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "AI/HSMonsterBase/HSMonsterAnimInstance.h"
#include "HSHangingBodyAnimInstance.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSHangingBodyAnimInstance : public UHSMonsterAnimInstance
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

#pragma endregion

#pragma region Calculate

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bFear = false;

#pragma endregion

};