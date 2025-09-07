// Made by LSH

#include "Spawner/HSSpawner_Base.h"
#include "Data/Spawn/SpawnInfo.h"
#include "GameSystem/Enum/HSEnumManager.h"

#pragma region Base

AHSSpawner_Base::AHSSpawner_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHSSpawner_Base::BeginPlay()
{
	Super::BeginPlay();

	FindObjectBPClasses();
	SpawnObjects();
}

void AHSSpawner_Base::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (auto DeleteObject : SpawnedObjects)
	{
		if (!DeleteObject)
		{
			continue;
		}

		DeleteObject->Destroy();
		DeleteObject = nullptr;
	}

	ObjectClasses.Empty();
	SpawnedObjects.Empty();

	Super::EndPlay(EndPlayReason);
}

#pragma endregion

#pragma region Setting

void AHSSpawner_Base::FindObjectBPClasses()
{
	if (!SpawnDataTable)
	{
		return;
	}

	FName CurrentMapName = HSEnumManager::GetEnumAsFName<EMapType>(UHSGameInstance::SelectedMap);

	for (int32 Index = 1; Index <= SpawnDataTable->GetRowMap().Num(); Index++)
	{
		FSpawnInfo* Data = GetObjectData(Index, EMapType::None);

		if (Data->Map_En != CurrentMapName)
		{
			continue;
		}

		FString BPClassPath = Data->Path;
		UClass* LoadClass = StaticLoadClass(AActor::StaticClass(), nullptr, *BPClassPath);

		ObjectClasses.Add(LoadClass);
	}
}

#pragma endregion