// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Delegates/DelegateCombinations.h"
#include "HSCharacterInteract.generated.h"

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCanInteract, bool, bCanInteract);

#pragma endregion

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOTEL_SECURITY_API UHSCharacterInteract : public UActorComponent
{
	GENERATED_BODY()

#pragma region Base

public:
	UHSCharacterInteract();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
	TObjectPtr<class AHSCharacter> Owner;

#pragma endregion

#pragma region Interact

public:
	FCanInteract CanInteract;

	class AHSInteractObjectBase* GetLineTraceHitObject() { return HitObject; }

protected:
	void CreateLineTrace();
	void CheckInteractObjectHitLineTrace(const FHitResult& LineTraceHit);

	UPROPERTY()
	TObjectPtr<class AHSInteractObjectBase> HitObject;

#pragma endregion

};