// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HSCharacterSound.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOTEL_SECURITY_API UHSCharacterSound : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHSCharacterSound(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void PlayBaseSound();

protected:
	UPROPERTY()
	TObjectPtr<class UAudioComponent> BaseAC;

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundWave> BaseSound;
};