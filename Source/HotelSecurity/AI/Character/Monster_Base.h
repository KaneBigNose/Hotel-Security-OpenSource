// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Character/Character/HSCharacter.h"
#include "Monster_Base.generated.h"

#pragma region Declare

UENUM(BlueprintType)
enum class EMonsterType : uint8
{
	BellyMan		UMETA(DisplayName = "BellyMan"),
	HotelManager	UMETA(DisplayName = "HotelManager"),
	BlackVeil		UMETA(DisplayName = "BlackVeil"),
	Miner			UMETA(DisplayName = "Miner"),
	HangingBody		UMETA(DisplayName = "HangingBody"),
	Nurse			UMETA(DisplayName = "Nurse"),
	Melodia			UMETA(DisplayName = "Melodia"),
	PlagueDoctor	UMETA(DisplayName = "PlagueDoctor"),
	TimeEater		UMETA(DisplayName = "TimeEater"),
	DeadWave		UMETA(DisplayName = "DeadWave"),
	Eclipser		UMETA(DisplayName = "Eclipser")
};

#pragma endregion

UCLASS()
class HOTEL_SECURITY_API AMonster_Base : public AHSCharacter
{
	GENERATED_BODY()

#pragma region Base

public:
	AMonster_Base(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void PossessedBy(AController* NewController) override;

#pragma endregion

#pragma region GAS

public:
	virtual class UHSAttributeSet* GetHSAttributeSet() override;

protected:
	UPROPERTY(EditAnywhere, Category = "HSCharacter|GAS")
	TObjectPtr<class UHSMonsterAttributeSet> MonsterAS;

#pragma endregion

#pragma region Overlap Event

protected:
	UFUNCTION()
	virtual void KillBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCapsuleComponent> KillCapsule;

#pragma endregion

#pragma region Time Stop

protected:
	UFUNCTION()
	virtual void MonsterStop(bool bIsStop);

protected:
	ECollisionEnabled::Type KillType;

#pragma endregion

};