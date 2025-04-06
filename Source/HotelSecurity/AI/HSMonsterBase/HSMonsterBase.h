// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HSMonsterBase.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSMonsterBase : public ACharacter
{
	GENERATED_BODY()

#pragma region Base

public:
	AHSMonsterBase();

#pragma endregion

#pragma region Overlap Event

public:
	UFUNCTION()
	void OnKillPlayerRangeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnInteractRangeDoorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnInteractRangeDoorEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	TArray<class AHSInteractDoor*> GetInInteractRangeDoors() { return InInteractRangeDoors; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* KillPlayerCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* InteractDoorCapsule;

	TArray<class AHSInteractDoor*> InInteractRangeDoors;

#pragma endregion

#pragma region Chase

public:
	virtual void SetChaseTargetMode();
	virtual void SetNormalMode();

	bool CheckChase() const { return bIsChased; }

protected:
	bool bIsChased = false;

#pragma endregion

};