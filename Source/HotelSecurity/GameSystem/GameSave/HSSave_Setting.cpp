// Made by LSH

#include "GameSystem/GameSave/HSSave_Setting.h"
#include "Kismet/GameplayStatics.h"

void UHSSave_Setting::LoadSettingData(int32& Anti, float& Frame, int32& Gra, FString& Lang, FIntPoint& Res, EWindowMode::Type& Scr, int32& Sha, float& Snd, TArray<int32>& IndexArr)
{
	UHSSave_Setting* Save_Setting = Cast<UHSSave_Setting>(UGameplayStatics::LoadGameFromSlot(TEXT("HSSave_Setting"), 0));

	if (!Save_Setting)
	{
		return;
	}

	Anti = Save_Setting->Value_AntiAliasing;
	Frame = Save_Setting->Value_Frame;
	Gra = Save_Setting->Value_Grapic;
	Lang = Save_Setting->Value_Language;
	Res = Save_Setting->Value_Resolution;
	Scr = static_cast<EWindowMode::Type>(Save_Setting->Value_Screen);
	Sha = Save_Setting->Value_Shadow;
	Snd = Save_Setting->Value_Sound;

	IndexArr[0] = Save_Setting->Index_Anti;
	IndexArr[1] = Save_Setting->Index_Frame;
	IndexArr[2] = Save_Setting->Index_Grapic;
	IndexArr[3] = Save_Setting->Index_Language;
	IndexArr[4] = Save_Setting->Index_Resolution;
	IndexArr[5] = Save_Setting->Index_Screen;
	IndexArr[6] = Save_Setting->Index_Shadow;
	IndexArr[7] = Save_Setting->Index_Sound;
}

void UHSSave_Setting::SaveSettingData(int32 Anti, float Frame, int32 Gra, FString Lang, FIntPoint Res, EWindowMode::Type Scr, int32 Sha, float Snd, TArray<int32> IndexArr)
{
	UHSSave_Setting* Save_Setting = Cast<UHSSave_Setting>(UGameplayStatics::CreateSaveGameObject(UHSSave_Setting::StaticClass()));

	Save_Setting->Value_AntiAliasing = Anti;
	Save_Setting->Value_Frame = Frame;
	Save_Setting->Value_Grapic = Gra;
	Save_Setting->Value_Language = Lang;
	Save_Setting->Value_Resolution = Res;
	Save_Setting->Value_Screen = static_cast<uint8>(Scr);
	Save_Setting->Value_Shadow = Sha;
	Save_Setting->Value_Sound = Snd;

	Save_Setting->Index_Anti = IndexArr[0];
	Save_Setting->Index_Frame = IndexArr[1];
	Save_Setting->Index_Grapic = IndexArr[2];
	Save_Setting->Index_Language = IndexArr[3];
	Save_Setting->Index_Resolution = IndexArr[4];
	Save_Setting->Index_Screen = IndexArr[5];
	Save_Setting->Index_Shadow = IndexArr[6];
	Save_Setting->Index_Sound = IndexArr[7];

	UGameplayStatics::SaveGameToSlot(Save_Setting, TEXT("HSSave_Setting"), 0);
}