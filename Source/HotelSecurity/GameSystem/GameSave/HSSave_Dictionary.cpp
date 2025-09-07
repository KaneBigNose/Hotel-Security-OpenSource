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

	case EMonsterType::DeadWave:
		return Save_Dictionary->bFindDeadWave;

	case EMonsterType::Eclipser:
		return Save_Dictionary->bFindEclipser;

	case EMonsterType::TimeEater:
		return Save_Dictionary->bFindTimeEater;
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
	Save_Dictionary->bFindDeadWave = LoadDictionaryData(EMonsterType::DeadWave);
	Save_Dictionary->bFindEclipser = LoadDictionaryData(EMonsterType::Eclipser);
	Save_Dictionary->bFindTimeEater = LoadDictionaryData(EMonsterType::TimeEater);

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

	case EMonsterType::DeadWave:
		Save_Dictionary->bFindDeadWave = true;
		break;

	case EMonsterType::Eclipser:
		Save_Dictionary->bFindEclipser = true;
		break;

	case EMonsterType::TimeEater:
		Save_Dictionary->bFindTimeEater = true;
		break;
	}

	UGameplayStatics::SaveGameToSlot(Save_Dictionary, TEXT("HSSave_Dictionary"), 0);
}