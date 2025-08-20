// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HSSave_Setting.generated.h"

UCLASS()
class HOTEL_SECURITY_API UHSSave_Setting : public USaveGame
{
	GENERATED_BODY()

public:
	void LoadSettingData(int32& Anti, float& Frame, int32& Gra, FString& Lang, FIntPoint& Res, EWindowMode::Type& Scr, int32& Sha, float& Snd, TArray<int32>& IndexArr);
	void SaveSettingData(int32 Anti, float Frame, int32 Gra, FString Lang, FIntPoint Res, EWindowMode::Type Scr, int32 Sha, float Snd, TArray<int32> IndexArr);
	
protected:
	UPROPERTY(SaveGame)
	int32 Value_AntiAliasing;

	UPROPERTY(SaveGame)
	float Value_Frame;

	UPROPERTY(SaveGame)
	int32 Value_Grapic;

	UPROPERTY(SaveGame)
	FString Value_Language;

	UPROPERTY(SaveGame)
	FIntPoint Value_Resolution;

	UPROPERTY(SaveGame)
	uint8 Value_Screen;

	UPROPERTY(SaveGame)
	int32 Value_Shadow;

	UPROPERTY(SaveGame)
	float Value_Sound;

protected:
	UPROPERTY(SaveGame)
	int32 Index_Anti;

	UPROPERTY(SaveGame)
	int32 Index_Frame;

	UPROPERTY(SaveGame)
	int32 Index_Grapic;

	UPROPERTY(SaveGame)
	int32 Index_Language;

	UPROPERTY(SaveGame)
	int32 Index_Resolution;

	UPROPERTY(SaveGame)
	int32 Index_Screen;

	UPROPERTY(SaveGame)
	int32 Index_Shadow;

	UPROPERTY(SaveGame)
	int32 Index_Sound;
};