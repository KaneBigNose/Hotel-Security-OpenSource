// Made by LSH

#include "GameSystem/GameInstance/HSGameInstance.h"
#include "GameSystem/Enum/HSEnumManager.h"
#include "GameSystem/GameSave/HSSave_Clear.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/PopUp/UI_PopUp_Base.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

EMapType UHSGameInstance::SelectedMap = EMapType::MainMenu;
ELanguageType UHSGameInstance::SelectedLanguage = ELanguageType::English;

UHSGameInstance::UHSGameInstance()
{
	static ConstructorHelpers::FClassFinder<UUI_PopUp_Base> ClearClassFinder(TEXT("/Game/HotelSecurity/UI/Blueprint/InGame/WBP_StageClear.WBP_StageClear_C"));
	if (ClearClassFinder.Succeeded())
	{
		StageClearClass = ClearClassFinder.Class;
	}

	static ConstructorHelpers::FClassFinder<UUI_PopUp_Base> CreditClassFinder(TEXT("/Game/HotelSecurity/UI/Blueprint/InGame/WBP_Credit.WBP_Credit_C"));
	if (CreditClassFinder.Succeeded())
	{
		CreditClass = CreditClassFinder.Class;
	}

	static ConstructorHelpers::FClassFinder<UUI_PopUp_Base> LoadingClassFinder(TEXT("/Game/HotelSecurity/UI/Blueprint/MainMenu/WBP_Loading.WBP_Loading_C"));
	if (LoadingClassFinder.Succeeded())
	{
		LoadingClass = LoadingClassFinder.Class;
	}
}

void UHSGameInstance::Init()
{
	Super::Init();

	FInternationalization::Get().SetCurrentCulture(TEXT("en"));

	StageClear.AddDynamic(this, &ThisClass::StageClearFunc);
}

void UHSGameInstance::Shutdown()
{
	SelectedMap = EMapType::MainMenu;

	Super::Shutdown();
}

#pragma endregion

#pragma region Map

void UHSGameInstance::OpenMap(const EMapType& MapType)
{
	SelectedMap = MapType;

	FName MapPath = FName(FString::Printf(TEXT("/Game/HotelSecurity/Map/%s"), *HSEnumManager::GetEnumAsFString<EMapType>(SelectedMap)));

	if (SelectedMap != EMapType::MainMenu)
	{
		UUI_Controller* UICon = GetSubsystem<UUI_Controller>();
		UICon->OpenStrongPopUpWidget(LoadingClass);

		FTimerHandle OpenHandle;
		GetWorld()->GetTimerManager().SetTimer(OpenHandle, [this, MapPath]()
			{
				UGameplayStatics::OpenLevel(GetWorld(), MapPath);
			}, 0.5f, false);

		return;
	}

	UGameplayStatics::OpenLevel(GetWorld(), MapPath);
}

#pragma endregion

#pragma region Stage Clear

void UHSGameInstance::StageClearFunc()
{
	UHSSave_Clear* Save_Clear = Cast<UHSSave_Clear>(UGameplayStatics::LoadGameFromSlot(TEXT("HSSave_Clear"), 0));
	Save_Clear->SaveClearData(SelectedMap);

	UUI_Controller* UICon = GetSubsystem<UUI_Controller>();

	if (SelectedMap == EMapType::OldMotel)
	{
		UICon->OpenPopUpWidget(CreditClass);

		return;
	}

	UICon->OpenPopUpWidget(StageClearClass);
}

#pragma endregion