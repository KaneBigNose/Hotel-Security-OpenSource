// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Anomaly/Enum/HSAnomalyEnum.h"
#include "HSAnomalyBase.generated.h"

UCLASS()
class HOTEL_SECURITY_API AHSAnomalyBase : public AActor
{
	GENERATED_BODY()

#pragma region Base

public:
	AHSAnomalyBase();

protected:
	virtual void BeginPlay() override;

protected:
	class UHSWorldSubsystem* Subsystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* AnomalyMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* AnomalyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* AnomalyChangeMesh;

#pragma endregion

#pragma region Data

protected:
	FVector DefaultLocation;
	FRotator DefaultRotation;
	FVector DefaultScale;

public:
	FName LocationData;
	FName ObjectData;
	FName AnomalyData;

#pragma endregion

#pragma region Anomaly Event

public:
	void StartRandomAnomaly(int32 ActorNum);

	bool CanApplyAnomalyEvent() { return !bApplyEvent; }

protected:
	TArray<EAnomalyType> Anomalys;

	EAnomalyType CurrentAnomaly = EAnomalyType::None;

	bool bApplyEvent = false;

	void Anomaly_Location(int32 ActorNum);
	void Anomaly_Rotation();
	void Anomaly_Scale();
	void Anomaly_Disappear();
	void Anomaly_Change(int32 ActorNum);
	void Anomaly_Fly();

#pragma endregion

#pragma region AnomalyFix

public:
	bool FixCurrentAnomaly(FName CheckLocation, FName CheckObject, FName CheckAnomaly);

protected:
	bool CheckCanFixAnomaly(FName CheckLocation, FName CheckObject, FName CheckAnomaly);

	void FixLocationAnomaly();
	void FixRotationAnomaly();
	void FixScaleAnomaly();
	void FixDisappearAnomaly();
	void FixChangeAnomaly();
	void FixFlyAnomaly();

#pragma endregion

};