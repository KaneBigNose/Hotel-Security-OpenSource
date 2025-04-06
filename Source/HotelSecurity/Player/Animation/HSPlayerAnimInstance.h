// Made by LSH

#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HSPlayerAnimInstance.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UHSPlayerAnimInstance(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	class AHSPlayer* HSPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	class AHSPlayerController* HSPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	class UCharacterMovementComponent* HSPlayerMovementComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FVector Velocity = FVector(0, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	float CurrentSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	bool bShouldMove = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	bool bIsSprint = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	bool bIsSitDown = false;
};