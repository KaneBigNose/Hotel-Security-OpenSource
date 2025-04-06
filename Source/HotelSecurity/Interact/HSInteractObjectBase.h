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
	AHSInteractObjectBase();

public:
	class UStaticMeshComponent* GetInteractObject() { return InteractObject; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	class UStaticMeshComponent* InteractObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	class USphereComponent* InteractRange;

#pragma endregion

#pragma region Interact

public:
	virtual void PlayerInteractThisObject();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	class UAudioComponent* InteractAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	class USoundWave* InteractSound;

	bool bIsInteracted = false;

#pragma endregion

};