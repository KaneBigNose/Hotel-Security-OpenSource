// Made by LSH

#include "GameSystem/GameSave/HSSave_Dictionary.h"
#include "Kismet/GameplayStatics.h"

bool UHSSave_Dictionary::LoadDictionaryData(EMonsterType MonsterName)
{
	UHSSave_Dictionary* Save_Dictionary = Cast<UHSSave_Dictionary>(UGameplayStatics::LoadGameFromSlot(TEXT("HSSave_Dictionary"), 0));

	if (!Save_Dictionary)
	{
		return false;
	}

	switch (MonsterName)
	{
	case EMonsterType::BellyMan:
		return Save_Dictionary->bFindBellyMan;

	case EMonsterType::HotelManager:
		return Save_Dictionary->bFindHotelManager;

	case EMonsterType::BlackVeil:
		return Save_Dictionary->bFindBlackVeil;

	case EMonsterType::Miner:
		return Save_Dictionary->bFindMiner;

	case EMonsterType::HangingBody:
		return Save_Dictionary->bFindHangingBody;

	case EMonsterType::Nurse:
		return Save_Dictionary->bFindNurse;

	case EMonsterType::Melodia:
		return Save_Dictionary->bFindMelodia;

	case EMonsterType::PlagueDoctor:
		return Save_Dictionary->bFindPlagueDoctor;
	}

	return false;
}

void UHSSave_Dictionary::SaveDictionaryData(EMonsterType MonsterName)
{
	UHSSave_Dictionary* Save_Dictionary = Cast<UHSSave_Dictionary>(UGameplayStatics::CreateSaveGameObject(UHSSave_Dictionary::StaticClass()));

	Save_Dictionary->bFindBellyMan = LoadDictionaryData(EMonsterType::BellyMan);
	Save_Dictionary->bFindHotelManager = LoadDictionaryData(EMonsterType::HotelManager);
	Save_Dictionary->bFindBlackVeil = LoadDictionaryData(EMonsterType::BlackVeil);
	Save_Dictionary->bFindMiner = LoadDictionaryData(EMonsterType::Miner);
	Save_Dictionary->bFindHangingBody = LoadDictionaryData(EMonsterType::HangingBody);
	Save_Dictionary->bFindNurse = LoadDictionaryData(EMonsterType::Nurse);
	Save_Dictionary->bFindMelodia = LoadDictionaryData(EMonsterType::Melodia);
	Save_Dictionary->bFindPlagueDoctor = LoadDictionaryData(EMonsterType::PlagueDoctor);

	switch (MonsterName)
	{
	case EMonsterType::BellyMan:
		Save_Dictionary->bFindBellyMan = true;
		break;

	case EMonsterType::HotelManager:
		Save_Dictionary->bFindHotelManager = true;
		break;

	case EMonsterType::BlackVeil:
		Save_Dictionary->bFindBlackVeil = true;
		break;

	case EMonsterType::Miner:
		Save_Dictionary->bFindMiner = true;
		break;

	case EMonsterType::HangingBody:
		Save_Dictionary->bFindHangingBody = true;
		break;

	case EMonsterType::Nurse:
		Save_Dictionary->bFindNurse = true;
		break;

	case EMonsterType::Melodia:
		Save_Dictionary->bFindMelodia = true;
		break;

	case EMonsterType::PlagueDoctor:
		Save_Dictionary->bFindPlagueDoctor = true;
		break;
	}

	UGameplayStatics::SaveGameToSlot(Save_Dictionary, TEXT("HSSave_Dictionary"), 0);
}