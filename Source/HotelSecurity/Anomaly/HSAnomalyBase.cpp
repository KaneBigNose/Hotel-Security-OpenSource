// Made by LSH

#include "Anomaly/HSAnomalyBase.h"
#include "Components/StaticMeshComponent.h"
#include "Anomaly/Data/Hotel/HotelAnomalyInfo.h"
#include "Anomaly/Data/Mine/MineAnomalyInfo.h"
#include "Enum/HSEnumManager.h"
#include "UI/Report/HSReportBaseWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Subsystem/Hotel/HotelSubsystem.h"
#include "Subsystem/Mine/MineSubsystem.h"
#include "Subsystem/Hospital/HospitalSubsystem.h"

#pragma region Base

AHSAnomalyBase::AHSAnomalyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	AnomalyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AnomalyMeshComponent"));
	RootComponent = AnomalyMeshComponent;
	AnomalyMeshComponent->SetRelativeScale3D(FVector(2, 2, 1.5f));

	if (AnomalyMesh)
	{
		AnomalyMeshComponent->SetStaticMesh(AnomalyMesh);
	}

	Anomalys.Add(EAnomalyType::Location);
	Anomalys.Add(EAnomalyType::Rotation);
	Anomalys.Add(EAnomalyType::Scale);
	Anomalys.Add(EAnomalyType::Disappear);
	Anomalys.Add(EAnomalyType::Change);
	Anomalys.Add(EAnomalyType::Fly);
}

void AHSAnomalyBase::BeginPlay()
{
	Super::BeginPlay();

	FString MapName = FPaths::GetCleanFilename(GetWorld()->GetMapName());

	if (MapName.EndsWith(TEXT("Hotel")))
	{
		Subsystem = GetWorld()->GetSubsystem<UHotelSubsystem>();
	}
	else if (MapName.EndsWith(TEXT("Mine")))
	{
		Subsystem = GetWorld()->GetSubsystem<UMineSubsystem>();
	}
	else if (MapName.EndsWith(TEXT("Hospital")))
	{
		Subsystem = GetWorld()->GetSubsystem<UHospitalSubsystem>();
	}
}

#pragma endregion

#pragma region Anomaly Event

void AHSAnomalyBase::StartRandomAnomaly(int32 ActorNum)
{
	int32 RandomInt = FMath::RandRange(0, Anomalys.Num() - 1);
	CurrentAnomaly = Anomalys[RandomInt];
	AnomalyData = HSEnumManager<EAnomalyType>::GetEnumAsFName(CurrentAnomaly);

	switch (CurrentAnomaly)
	{
	case EAnomalyType::Location: // 1
		Anomaly_Location(ActorNum);
		break;

	case EAnomalyType::Rotation: // 2
		Anomaly_Rotation();
		break;

	case EAnomalyType::Scale: // 3
		Anomaly_Scale();
		break;

	case EAnomalyType::Disappear: //4
		Anomaly_Disappear();
		break;

	case EAnomalyType::Change: // 5
		Anomaly_Change(ActorNum);
		break;

	case EAnomalyType::Fly: // 6
		Anomaly_Fly();
		break;
	}

	bApplyEvent = true;
}

void AHSAnomalyBase::Anomaly_Location(int32 ActorNum)
{
	DefaultLocation = GetActorLocation();

	FVector TargetLocation = FVector::ZeroVector;
	TargetLocation.X = Subsystem->GetAnomalyData(ActorNum + 1)->CLocationX;
	TargetLocation.Y = Subsystem->GetAnomalyData(ActorNum + 1)->CLocationY;
	TargetLocation.Z = Subsystem->GetAnomalyData(ActorNum + 1)->CLocationZ;

	SetActorLocation(TargetLocation);
}

void AHSAnomalyBase::Anomaly_Rotation()
{
	int32 RandomInt1 = FMath::RandRange(-40, 40);
	int32 RandomInt2 = FMath::RandRange(-40, 40);
	int32 RandomInt3 = FMath::RandRange(-40, 40);

	DefaultRotation = AnomalyMeshComponent->GetRelativeRotation();
	FRotator TargetRotation = DefaultRotation;

	TargetRotation.Pitch += RandomInt1;
	TargetRotation.Yaw += RandomInt2;
	TargetRotation.Roll += RandomInt3;

	SetActorRotation(TargetRotation);
}

void AHSAnomalyBase::Anomaly_Scale()
{
	DefaultScale = AnomalyMeshComponent->GetRelativeScale3D();

	FVector ChangeScaleValue = DefaultScale;

	int32 RandomInt = FMath::RandRange(0, 1);

	if (RandomInt == 0)
	{
		ChangeScaleValue *= 0.5f;
	}
	else
	{
		ChangeScaleValue *= 1.5f;
	}

	AnomalyMeshComponent->SetRelativeScale3D(ChangeScaleValue);
}

void AHSAnomalyBase::Anomaly_Disappear()
{
	AnomalyMeshComponent->SetVisibility(false);
}

void AHSAnomalyBase::Anomaly_Change(int32 ActorNum)
{
	if (!AnomalyMesh || !AnomalyChangeMesh)
	{
		StartRandomAnomaly(ActorNum);
		return;
	}

	AnomalyMeshComponent->SetStaticMesh(AnomalyChangeMesh);
}

void AHSAnomalyBase::Anomaly_Fly()
{
	DefaultLocation = GetActorLocation();

	FVector CurrentLocation = AnomalyMeshComponent->GetRelativeLocation();
	FVector TargetLocation = CurrentLocation;
	TargetLocation.Z += 40;

	SetActorLocation(TargetLocation);
}

#pragma endregion

#pragma region Anomaly Fix

bool AHSAnomalyBase::FixCurrentAnomaly(FName CheckLocation, FName CheckObject, FName CheckAnomaly)
{
	if (!CheckCanFixAnomaly(CheckLocation, CheckObject, CheckAnomaly))
	{
		return false;
	}

	switch (CurrentAnomaly)
	{
	case EAnomalyType::Location:
		FixLocationAnomaly();
		break;

	case EAnomalyType::Rotation:
		FixRotationAnomaly();
		break;

	case EAnomalyType::Scale:
		FixScaleAnomaly();
		break;

	case EAnomalyType::Disappear:
		FixDisappearAnomaly();
		break;

	case EAnomalyType::Change:
		FixChangeAnomaly();
		break;

	case EAnomalyType::Fly:
		FixFlyAnomaly();
		break;
	}

	bApplyEvent = false;
	return true;
}

bool AHSAnomalyBase::CheckCanFixAnomaly(FName CheckLocation, FName CheckObject, FName CheckAnomaly)
{
	if (CanApplyAnomalyEvent() || LocationData != CheckLocation || ObjectData != CheckObject || AnomalyData != CheckAnomaly)
	{
		Subsystem->FailedFixAnomaly();
		return false;
	}

	Subsystem->SucceedFixAnomaly();
	return true;
}

void AHSAnomalyBase::FixLocationAnomaly()
{
	SetActorLocation(DefaultLocation);
}

void AHSAnomalyBase::FixRotationAnomaly()
{
	SetActorRotation(DefaultRotation);
}

void AHSAnomalyBase::FixScaleAnomaly()
{
	AnomalyMeshComponent->SetRelativeScale3D(DefaultScale);
}

void AHSAnomalyBase::FixDisappearAnomaly()
{
	AnomalyMeshComponent->SetVisibility(true);
}

void AHSAnomalyBase::FixChangeAnomaly()
{
	AnomalyMeshComponent->SetStaticMesh(AnomalyMesh);
}

void AHSAnomalyBase::FixFlyAnomaly()
{
	SetActorLocation(DefaultLocation);
}

#pragma endregion