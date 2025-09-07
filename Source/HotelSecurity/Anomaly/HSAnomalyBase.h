// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HSAnomalyBase.generated.h"

#pragma region Declare

UENUM(BlueprintType)
enum class EAnomalyType : uint8
{
	None		UMETA(DisplayName = "None"),
	Move		UMETA(DisplayName = "Move"),
	Rotate		UMETA(DisplayName = "Rotate"),
	Expand		UMETA(DisplayName = "Expand"),
	Shrink		UMETA(DisplayName = "Shrink"),
	Disappear	UMETA(DisplayName = "Disappear"),
	Change		UMETA(DisplayName = "Change"),
	Fly			UMETA(DisplayName = "Fly"),
	Darkness	UMETA(DisplayName = "Darkness"),
	Ghost		UMETA(DisplayName = "Ghost")
};

#pragma endregion

UCLASS()
class HOTEL_SECURITY_API AHSAnomalyBase : public AActor
{
	GENERATED_BODY()

#pragma region Base

public:
	AHSAnomalyBase();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UPROPERTY()
	TObjectPtr<class UHSWorldSubsystem> Subsystem;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> AnomalyMeshComponent;

#pragma endregion

#pragma region Data

public:
	FString PlaceData;
	FString ObjectData;
	FString AnomalyData;

#pragma endregion

#pragma region Preview

public:
	void CaptureObject();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USceneCaptureComponent2D> PreviewComp;

	UPROPERTY()
	TObjectPtr<class UTextureRenderTarget2D> ObjectPreview;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USpotLightComponent> PreviewLight;

#pragma endregion

#pragma region Localization

protected:
	static FText PlaceText;
	static FText ObjectText;
	static FText AnomalyText;

#pragma endregion

#pragma region Anomaly Event

public:
	void StartRandomAnomaly(int32 ActorNum);

protected:
	void SettingAnomalyData();

	void Anomaly_Move(int32 ActorNum);
	void Anomaly_Rotate();
	void Anomaly_Expand();
	void Anomaly_Shrink();
	void Anomaly_Disappear();
	void Anomaly_Change(int32 ActorNum);
	void Anomaly_Fly(int32 ActorNum);
	void Anomaly_Darkness(int32 ActorNum);
	void Anomaly_Ghost(int32 ActorNum);

public:
	bool bApplyEvent = true;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMesh> AnomalyMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMesh> AnomalyChangeMesh;

	UPROPERTY()
	TObjectPtr<class UMaterial> DarknessMaterial;

	UPROPERTY()
	TObjectPtr<class UMaterialInterface> DefalutMaterial;

	UPROPERTY()
	TObjectPtr<class UMaterial> GhostMaterial;

protected:
	static TArray<EAnomalyType> Anomalys;

	EAnomalyType CurrentAnomaly = EAnomalyType::None;

	FTimerHandle SmoothHandle;

	FVector DefaultLocation;
	FRotator DefaultRotation;
	FVector DefaultScale;

	UPROPERTY(EditAnywhere)
	bool bCanFly = true;

#pragma endregion

#pragma region AnomalyFix

public:
	bool FixCurrentAnomaly(FString CheckPlace, FString CheckObject, FString CheckAnomaly);

protected:
	bool CheckCanFix(FString CheckPlace, FString CheckObject, FString CheckAnomaly);

	void Fix_Move();
	void Fix_Rotate();
	void Fix_Expand();
	void Fix_Shrink();
	void Fix_Disappear();
	void Fix_Change();
	void Fix_Fly();
	void Fix_Darkness();
	void Fix_Ghost();

#pragma endregion

};