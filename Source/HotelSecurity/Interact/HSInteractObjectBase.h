// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HSInteractObjectBase.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSInteractObjectBase : public AActor
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AHSInteractObjectBase(const FObjectInitializer& ObjectInitializer);

public:
	class UStaticMeshComponent* GetInteractObject() { return InteractObject; }

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> InteractObject;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USphereComponent> InteractRange;

#pragma endregion

#pragma region Interact

public:
	virtual void InteractThisObject();

protected:
	UPROPERTY(EditAnywhere, Category = "Interact")
	TObjectPtr<class UAudioComponent> InteractAC;

	UPROPERTY(EditAnywhere, Category = "Interact")
	TObjectPtr<class USoundWave> InteractSound;

	bool bIsInteracted = false;

#pragma endregion

};