// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HSPlayerInteract.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOTEL_SECURITY_API UHSPlayerInteract : public UActorComponent
{
	GENERATED_BODY()

#pragma region Base

public:
	UHSPlayerInteract();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
	class AHSPlayer* HSPlayer;

#pragma endregion

#pragma region Interact

public:
	class AHSInteractObjectBase* GetLineTraceHitObject() { return HitObject; }

protected:
	class AHSInteractObjectBase* HitObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LineTraceLength = 300.f;

	void CreateLineTrace();
	void CheckInteractObjectHitLineTrace(TArray<FHitResult> LineTraceHits);

public:
	bool PlayerCanInteract() { return bCanInteract; }
	void CanInteractTimer();

protected:
	FTimerHandle CanInteractHandle;

	bool bCanInteract = true;

	void CanInteract();

#pragma endregion

};