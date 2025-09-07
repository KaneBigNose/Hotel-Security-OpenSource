// Made by LSH

#include "Spawner/Anomaly/HSSpawner_Anomaly.h"
#include "Data/Spawn/Anomaly/SpawnInfo_Anomaly.h"
#include "Anomaly/HSAnomalyBase.h"
#include "GameSystem/GameInstance/HSGameInstance.h"
#include "GameSystem/Enum/HSEnumManager.h"

#pragma region Data

FSpawnInfo* AHSSpawner_Anomaly::GetObjectData(int32 RowNum, EMapType CurrentMap)
{
	int32 TargetRowNum = RowNum;

	switch (CurrentMap)
	{
	case EMapType::None:
		TargetRowNum += 0;
		break;

	case EMapType::Hotel:
		TargetRowNum += 0;
		break;

	case EMapType::Mine:
		TargetRowNum += 36;
		break;

	case EMapType::Hospital:
		TargetRowNum += 58;
		break;

	case EMapType::OldMotel:
		TargetRowNum += 85;
		break;
	}

	return SpawnDataTable->FindRow<FSpawnInfo>(*FString::FromInt(TargetRowNum), TEXT(""));
}

FSpawnInfo* AHSSpawner_Anomaly::GetObjectData(FString TargetName, FString TargetPlace)
{
	FSpawnInfo_Anomaly* AnomalyInfo = nullptr;

	for (auto RowData : SpawnDataTable->GetRowMap())
	{
		AnomalyInfo = (FSpawnInfo_Anomaly*)RowData.Value;

		if (AnomalyInfo->Object_En == TargetName && AnomalyInfo->Place_En == TargetPlace)
		{
			return AnomalyInfo;
		}
		else if (AnomalyInfo->Object_Ko == TargetName && AnomalyInfo->Place_Ko == TargetPlace)
		{
			return AnomalyInfo;
		}
	}

	return (FSpawnInfo*)AnomalyInfo;
}

#pragma endregion

#pragma region Setting

void AHSSpawner_Anomaly::SpawnObjects()
{
	for (int32 Index = 1; Index <= ObjectClasses.Num(); Index++)
	{
		FSpawnInfo_Anomaly* Data = static_cast<FSpawnInfo_Anomaly*>(GetObjectData(Index));

		FVector SpawnLocation = FVector(Data->LocationX, Data->LocationY, Data->LocationZ);
		FRotator SpawnRotation = FRotator(Data->RotationY, Data->RotationZ, Data->RotationX);

		AActor* SpawnedObject = GetWorld()->SpawnActor<AActor>(ObjectClasses[Index - 1], SpawnLocation, SpawnRotation);

		if (UHSGameInstance::SelectedLanguage == ELanguageType::English)
		{
			Cast<AHSAnomalyBase>(SpawnedObject)->PlaceData = Data->Place_En;
			Cast<AHSAnomalyBase>(SpawnedObject)->ObjectData = Data->Object_En;
		}
		else if (UHSGameInstance::SelectedLanguage == ELanguageType::Korean)
		{
			Cast<AHSAnomalyBase>(SpawnedObject)->PlaceData = Data->Place_Ko;
			Cast<AHSAnomalyBase>(SpawnedObject)->ObjectData = Data->Object_Ko;
		}
		
		SpawnedObjects.Add(SpawnedObject);
	}
}

#pragma endregion