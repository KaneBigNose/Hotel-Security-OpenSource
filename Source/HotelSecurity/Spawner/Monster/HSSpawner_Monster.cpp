// Made by LSH

#include "Spawner/Monster/HSSpawner_Monster.h"
#include "GameSystem/Enum/HSEnumManager.h"
#include "GameSystem/GameSave/HSSave_Dictionary.h"
#include "Data/Spawn/Monster/SpawnInfo_Monster.h"
#include "AI/Character/Monster_Base.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

void AHSSpawner_Monster::BeginPlay()
{
	Super::BeginPlay();

	UHSGameInstance* GameInstance = GetWorld()->GetGameInstance<UHSGameInstance>();
	if (GameInstance->SelectedMap != EMapType::Mine)
	{
		return;
	}

	FTimerHandle HangingBodyHandle;
	TimerHandles.Add(HangingBodyHandle);
	GetWorld()->GetTimerManager().SetTimer(HangingBodyHandle, [this]()
		{
			FSpawnInfo_Monster* Data = static_cast<FSpawnInfo_Monster*>(GetObjectData(7, EMapType::None));

			FVector SpawnLocation = FVector(Data->LocationX, Data->LocationY, Data->LocationZ);
			GetWorld()->SpawnActor<AActor>(ObjectClasses[3], SpawnLocation, FRotator::ZeroRotator);
		}, 100.f, true);
}

void AHSSpawner_Monster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (auto Target : TimerHandles)
	{
		GetWorld()->GetTimerManager().ClearTimer(Target);
	}

	Super::EndPlay(EndPlayReason);
}

#pragma endregion

#pragma region Data

FSpawnInfo* AHSSpawner_Monster::GetObjectData(int32 RowNum, EMapType CurrentMap)
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
		TargetRowNum += 3;
		break;

	case EMapType::Hospital:
		TargetRowNum += 7;
		break;

	case EMapType::OldMotel:
		TargetRowNum += 11;
		break;
	}

	return SpawnDataTable->FindRow<FSpawnInfo>(*FString::FromInt(TargetRowNum), TEXT(""));
}

FSpawnInfo* AHSSpawner_Monster::GetObjectData(FString TargetName, FString TargetPlace)
{
	FSpawnInfo_Monster* MonsterInfo = nullptr;

	FString CurrentMapName = HSEnumManager::GetEnumAsFString<EMapType>(UHSGameInstance::SelectedMap);

	for (auto RowData : SpawnDataTable->GetRowMap())
	{
		MonsterInfo = (FSpawnInfo_Monster*)RowData.Value;

		if (MonsterInfo->Name == TargetName && MonsterInfo->Map_En == CurrentMapName)
		{
			return MonsterInfo;
		}
	}

	return (FSpawnInfo*)MonsterInfo;
}

#pragma endregion

#pragma region Setting

void AHSSpawner_Monster::SpawnObjects()
{
	for (int32 Index = 1; Index <= ObjectClasses.Num(); Index++)
	{
		FSpawnInfo_Monster* Data = static_cast<FSpawnInfo_Monster*>(GetObjectData(Index));

		FVector SpawnLocation = FVector(Data->LocationX, Data->LocationY, Data->LocationZ);
		float SpawnDuration = Data->SpawnDuration;

		TSubclassOf<AActor> ObjectClass = ObjectClasses[Index - 1];
		EMonsterType MonsterName = Data->MonsterName;

		FTimerHandle SpawnHandle;
		TimerHandles.Add(SpawnHandle);
		GetWorld()->GetTimerManager().SetTimer(SpawnHandle, [this, Index, SpawnLocation, ObjectClass, MonsterName]()
		{
			if (!IsValid(this) || !ObjectClass || !GetWorld())
			{
				return;
			}

			AActor* SpawnedMonster = GetWorld()->SpawnActor<AActor>(ObjectClass, SpawnLocation, FRotator::ZeroRotator);
			SpawnedObjects.Add(SpawnedMonster);

			UHSSave_Dictionary* Save_Dictionary = Cast<UHSSave_Dictionary>(UGameplayStatics::LoadGameFromSlot(TEXT("HSSave_Dictionary"), 0));
			Save_Dictionary->SaveDictionaryData(MonsterName);
		}, SpawnDuration, false);
	}
}

#pragma endregion