// Made by LSH

#include "Anomaly/HSAnomalyBase.h"
#include "GameSystem/Enum/HSEnumManager.h"
#include "GameSystem/Subsystem/HSWorldSubsystem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SpotLightComponent.h"
#include "Data/Spawn/Anomaly/SpawnInfo_Anomaly.h"
#include "Engine/TextureRenderTarget2D.h"

#pragma region Base

AHSAnomalyBase::AHSAnomalyBase()
{
	PrimaryActorTick.bCanEverTick = false;

	AnomalyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AnomalyMeshComponent"));
	RootComponent = AnomalyMeshComponent;
	AnomalyMeshComponent->SetRelativeScale3D(FVector(2, 2, 1.5f));

	PreviewComp = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("PreviewComp"));
	PreviewComp->SetupAttachment(RootComponent);
	PreviewComp->SetRelativeLocationAndRotation(FVector(0, 80, 80), FRotator(-20, -90, 0));
	PreviewComp->bCaptureEveryFrame = false;
	PreviewComp->bCaptureOnMovement = false;

	PreviewLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("PreviewLight"));
	PreviewLight->SetupAttachment(PreviewComp);
	PreviewLight->Intensity = 1500;
	PreviewLight->AttenuationRadius = 500;
	PreviewLight->OuterConeAngle = 80;
	PreviewLight->bAffectsWorld = false;

	DarknessComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DarknessComp"));
	DarknessComp->SetupAttachment(AnomalyMeshComponent);

	static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> ObjectPreviewFinder(TEXT("/AssetContent/Texture/UI/Report/ObjectPreview.ObjectPreview"));
	if (ObjectPreviewFinder.Succeeded())
	{
		ObjectPreview = ObjectPreviewFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> DarknessMaterialFinder(TEXT("/AssetContent/Material/Anomaly/Darkness.Darkness"));
	if (DarknessMaterialFinder.Succeeded())
	{
		DarknessMaterial = DarknessMaterialFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> GhostMaterialFinder(TEXT("/AssetContent/Material/Anomaly/Ghost.Ghost"));
	if (GhostMaterialFinder.Succeeded())
	{
		GhostMaterial = GhostMaterialFinder.Object;
	}

	Anomalys.Add(EAnomalyType::Move);
	Anomalys.Add(EAnomalyType::Rotate);
	Anomalys.Add(EAnomalyType::Expand);
	Anomalys.Add(EAnomalyType::Shrink);
	Anomalys.Add(EAnomalyType::Disappear);
	Anomalys.Add(EAnomalyType::Change);
	Anomalys.Add(EAnomalyType::Fly);
	Anomalys.Add(EAnomalyType::Darkness);
	Anomalys.Add(EAnomalyType::Ghost);
}

void AHSAnomalyBase::BeginPlay()
{
	Super::BeginPlay();

	Subsystem = GetWorld()->GetSubsystem<UHSWorldSubsystem>();

	DefaultLocation = GetActorLocation();
	DefaultRotation = AnomalyMeshComponent->GetRelativeRotation();
	DefaultScale = AnomalyMeshComponent->GetRelativeScale3D();

	if (AnomalyMeshComponent->GetStaticMesh())
	{
		DefalutMaterial = AnomalyMeshComponent->GetStaticMesh()->GetMaterial(0)->GetMaterial();
	}

	PreviewComp->TextureTarget = ObjectPreview;
}

#pragma endregion

#pragma region Preview

void AHSAnomalyBase::CaptureObject()
{
	PreviewLight->bAffectsWorld = true;
	PreviewLight->MarkRenderStateDirty();

	PreviewComp->CaptureScene();

	FTimerHandle TurnOffHandle;
	GetWorld()->GetTimerManager().SetTimer(TurnOffHandle, [this]()
		{
			PreviewLight->bAffectsWorld = false;
			PreviewLight->MarkRenderStateDirty();
		}, 0.1f, false);
}

#pragma endregion

#pragma region Anomaly Event

void AHSAnomalyBase::StartRandomAnomaly(int32 ActorNum)
{
	int32 RandomInt = FMath::RandRange(0, Anomalys.Num() - 1);
	CurrentAnomaly = Anomalys[RandomInt];
	AnomalyData = HSEnumManager::GetEnumAsFString<EAnomalyType>(CurrentAnomaly);

	switch (CurrentAnomaly)
	{
	case EAnomalyType::Move:
		Anomaly_Move(ActorNum);
		break;

	case EAnomalyType::Rotate:
		Anomaly_Rotate();
		break;

	case EAnomalyType::Expand:
		Anomaly_Expand();
		break;

	case EAnomalyType::Shrink:
		Anomaly_Shrink();
		break;

	case EAnomalyType::Disappear:
		Anomaly_Disappear();
		break;

	case EAnomalyType::Change:
		Anomaly_Change(ActorNum);
		break;

	case EAnomalyType::Fly:
		Anomaly_Fly(ActorNum);
		break;

	case EAnomalyType::Darkness:
		Anomaly_Darkness();
		break;

	case EAnomalyType::Ghost:
		Anomaly_Ghost(ActorNum);
		break;
	}

	bApplyEvent = false;
}

void AHSAnomalyBase::Anomaly_Move(int32 ActorNum)
{
	FSpawnInfo_Anomaly* Data = Subsystem->GetAnomalyData(ActorNum);
	FVector TargetLocation(Data->CLocationX, Data->CLocationY, Data->CLocationZ);

	GetWorld()->GetTimerManager().SetTimer(SmoothHandle, [this, TargetLocation]()
		{
			FVector SmoothLocation = FMath::VInterpTo(GetActorLocation(), TargetLocation, GetWorld()->GetDeltaSeconds(), 2);
			SetActorLocation(SmoothLocation);

			if (SmoothLocation.Equals(TargetLocation, 0.1f))
			{
				GetWorld()->GetTimerManager().ClearTimer(SmoothHandle);
			}
		}, 0.01f, true);
}

void AHSAnomalyBase::Anomaly_Rotate()
{
	int32 RandomInt1 = FMath::RandRange(-40, 40);
	int32 RandomInt2 = FMath::RandRange(-40, 40);
	int32 RandomInt3 = FMath::RandRange(-40, 40);

	FRotator TargetRotation = DefaultRotation;
	TargetRotation.Pitch += RandomInt1;
	TargetRotation.Yaw += RandomInt2;
	TargetRotation.Roll += RandomInt3;

	GetWorld()->GetTimerManager().SetTimer(SmoothHandle, [this, TargetRotation]()
		{
			FRotator SmoothRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 2);
			SetActorRotation(SmoothRotation);

			if (SmoothRotation.Equals(TargetRotation, 0.1f))
			{
				GetWorld()->GetTimerManager().ClearTimer(SmoothHandle);
			}
		}, 0.01f, true);
}

void AHSAnomalyBase::Anomaly_Expand()
{
	FVector TargetScale = DefaultScale * 1.5f;

	GetWorld()->GetTimerManager().SetTimer(SmoothHandle, [this, TargetScale]()
		{
			FVector SmoothScale = FMath::VInterpTo(AnomalyMeshComponent->GetRelativeScale3D(), TargetScale, GetWorld()->GetDeltaSeconds(), 2);
			AnomalyMeshComponent->SetRelativeScale3D(SmoothScale);

			if (SmoothScale.Equals(TargetScale, 0.1f))
			{
				GetWorld()->GetTimerManager().ClearTimer(SmoothHandle);
			}
		}, 0.01f, true);
}

void AHSAnomalyBase::Anomaly_Shrink()
{
	FVector TargetScale = DefaultScale * 0.5f;

	GetWorld()->GetTimerManager().SetTimer(SmoothHandle, [this, TargetScale]()
		{
			FVector SmoothScale = FMath::VInterpTo(AnomalyMeshComponent->GetRelativeScale3D(), TargetScale, GetWorld()->GetDeltaSeconds(), 2);
			AnomalyMeshComponent->SetRelativeScale3D(SmoothScale);

			if (SmoothScale.Equals(TargetScale, 0.1f))
			{
				GetWorld()->GetTimerManager().ClearTimer(SmoothHandle);
			}
		}, 0.01f, true);
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

void AHSAnomalyBase::Anomaly_Fly(int32 ActorNum)
{
	if (!bCanFly)
	{
		StartRandomAnomaly(ActorNum);
		return;
	}

	FVector TargetFlyLocation = AnomalyMeshComponent->GetRelativeLocation();
	TargetFlyLocation.Z += 50;

	bool bUp = false;

	GetWorld()->GetTimerManager().SetTimer(SmoothHandle, [this, TargetFlyLocation, bUp]() mutable
		{
			FVector SmoothLocation = FMath::VInterpTo(AnomalyMeshComponent->GetRelativeLocation(), TargetFlyLocation, GetWorld()->GetDeltaSeconds(), 1);
			AnomalyMeshComponent->SetRelativeLocation(SmoothLocation);

			if (SmoothLocation.Equals(TargetFlyLocation, 0.1f))
			{
				if (bUp)
				{
					TargetFlyLocation.Z += 10;
				}
				else
				{
					TargetFlyLocation.Z -= 10;
				}

				bUp = !bUp;
			}
		}, 0.01f, true);
}

void AHSAnomalyBase::Anomaly_Darkness()
{
	UMaterialInstanceDynamic* DynMat = UMaterialInstanceDynamic::Create(DarknessMaterial, this);
	APostProcessVolume* PostProcessVolume = GetWorld()->SpawnActor<APostProcessVolume>();
	FVector SphereLocation = DarknessComp->GetComponentLocation();

	PostProcessVolume->bUnbound = true;
	PostProcessVolume->Settings.WeightedBlendables.Array.Add(FWeightedBlendable(1, DynMat));

	DynMat->SetVectorParameterValue(TEXT("SphereCenter"), FLinearColor(SphereLocation.X, SphereLocation.Y, SphereLocation.Z, 0));
	DynMat->SetScalarParameterValue(TEXT("SphereRadius"), DarknessRadius);

	float CurrentColor = 1;
	const float TargetColor = 0.05f;

	GetWorld()->GetTimerManager().SetTimer(SmoothHandle, [this, DynMat, CurrentColor, TargetColor]() mutable
		{
			CurrentColor -= 0.02f;
			DynMat->SetScalarParameterValue("Smooth", CurrentColor);

			if (CurrentColor <= TargetColor)
			{
				CurrentColor = 1;
				GetWorld()->GetTimerManager().ClearTimer(SmoothHandle);
			}
		}, 0.1f, true);
}

void AHSAnomalyBase::Anomaly_Ghost(int32 ActorNum)
{
	if (!AnomalyMeshComponent->GetStaticMesh())
	{
		StartRandomAnomaly(ActorNum);
		return;
	}

	UMaterialInstanceDynamic* DynMat = UMaterialInstanceDynamic::Create(GhostMaterial, this);
	AnomalyMeshComponent->SetMaterial(0, DynMat);

	float CurrentAlpha = 1;
	const float TargetAlpha = 0.05f;

	GetWorld()->GetTimerManager().SetTimer(SmoothHandle, [this, DynMat, CurrentAlpha, TargetAlpha]() mutable
		{
			CurrentAlpha -= 0.02f;
			DynMat->SetScalarParameterValue("Opacity", CurrentAlpha);

			if (CurrentAlpha <= TargetAlpha)
			{
				CurrentAlpha = 1;
				GetWorld()->GetTimerManager().ClearTimer(SmoothHandle);
			}
		}, 0.1f, true);
}

#pragma endregion

#pragma region Anomaly Fix

bool AHSAnomalyBase::FixCurrentAnomaly(FString CheckLocation, FString CheckObject, FString CheckAnomaly)
{
	if (!CheckCanFix(CheckLocation, CheckObject, CheckAnomaly))
	{
		return false;
	}

	switch (CurrentAnomaly)
	{
	case EAnomalyType::Move:
		Fix_Move();
		break;

	case EAnomalyType::Rotate:
		Fix_Rotate();
		break;

	case EAnomalyType::Expand:
		Fix_Expand();
		break;

	case EAnomalyType::Shrink:
		Fix_Shrink();
		break;

	case EAnomalyType::Disappear:
		Fix_Disappear();
		break;

	case EAnomalyType::Change:
		Fix_Change();
		break;

	case EAnomalyType::Fly:
		Fix_Fly();
		break;

	case EAnomalyType::Darkness:
		Fix_Darkness();
		break;

	case EAnomalyType::Ghost:
		Fix_Ghost();
		break;
	}

	bApplyEvent = true;
	return true;
}

bool AHSAnomalyBase::CheckCanFix(FString CheckLocation, FString CheckObject, FString CheckAnomaly)
{
	if (bApplyEvent || LocationData != CheckLocation || ObjectData != CheckObject || AnomalyData != CheckAnomaly)
	{
		Subsystem->FailedFixAnomaly();
		return false;
	}

	GetWorld()->GetTimerManager().ClearTimer(SmoothHandle);
	Subsystem->SucceedFixAnomaly();
	return true;
}

void AHSAnomalyBase::Fix_Move()
{
	SetActorLocation(DefaultLocation);
}

void AHSAnomalyBase::Fix_Rotate()
{
	SetActorRotation(DefaultRotation);
}

void AHSAnomalyBase::Fix_Expand()
{
	AnomalyMeshComponent->SetRelativeScale3D(DefaultScale);
}

void AHSAnomalyBase::Fix_Shrink()
{
	AnomalyMeshComponent->SetRelativeScale3D(DefaultScale);
}

void AHSAnomalyBase::Fix_Disappear()
{
	AnomalyMeshComponent->SetVisibility(true);
}

void AHSAnomalyBase::Fix_Change()
{
	AnomalyMeshComponent->SetStaticMesh(AnomalyMesh);
}

void AHSAnomalyBase::Fix_Fly()
{
	SetActorLocation(DefaultLocation);
}

void AHSAnomalyBase::Fix_Darkness()
{

}

void AHSAnomalyBase::Fix_Ghost()
{
	UMaterialInstanceDynamic* DynMat = UMaterialInstanceDynamic::Create(DefalutMaterial, this);
	AnomalyMeshComponent->SetMaterial(0, DynMat);
}

#pragma endregion