// Made by LSH

#include "GameInstance/HSGameInstance.h"
#include "UI/StageClear/HSStageClearWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Player/HSPlayer/HSPlayer.h"
#include "Internationalization/Internationalization.h"
#include "GameSave/HSGameSave.h"

#pragma region Base

UHSGameInstance::UHSGameInstance()
{
	static ConstructorHelpers::FClassFinder<UHSStageClearWidget> StageClearClassFinder(TEXT("/Game/HotelSecurity/UI/Blueprint/StageClear/WBP_StageClear.WBP_StageClear_C"));
	if (StageClearClassFinder.Succeeded())
	{
		StageClearClass = StageClearClassFinder.Class;
	}
}

void UHSGameInstance::Init()
{
	Super::Init();

	FInternationalization::Get().SetCurrentCulture(TEXT("en"));

	StageClearDelegate.AddDynamic(this, &ThisClass::CreateStageClearWidget);

	LoadGameSaveData();
}

#pragma endregion

#pragma region Stage Clear

void UHSGameInstance::CreateStageClearWidget()
{
	if (!StageClearClass)
	{
		return;
	}

	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetController());

	StageClearWidget = Cast<UHSStageClearWidget>(CreateWidget(GetWorld(), StageClearClass));
	StageClearWidget->AddToViewport();

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetWidgetToFocus(StageClearWidget->TakeWidget());
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;

	UGameplayStatics::SetGamePaused(GetWorld(), true);

	SetCurrentOpenWidget(StageClearWidget);

	SaveGameSaveData();
}

#pragma endregion

#pragma region Save

void UHSGameInstance::LoadGameSaveData()
{
	UHSGameSave* HSSaveGame = Cast<UHSGameSave>(UGameplayStatics::LoadGameFromSlot(TEXT("HSGameSaveSlot"), 0));

	if (!HSSaveGame)
	{
		return;
	}

	bIsClearHotel = HSSaveGame->bIsClearHotel;
	bIsClearMine = HSSaveGame->bIsClearMine;
	bIsClearHospital = HSSaveGame->bIsClearHospital;
}

void UHSGameInstance::SaveGameSaveData()
{
	UHSGameSave* SaveGameInstance = Cast<UHSGameSave>(UGameplayStatics::CreateSaveGameObject(UHSGameSave::StaticClass()));

	if (SelectedMapName == FName("Hotel"))
	{
		bIsClearHotel = true;
	}
	else if (SelectedMapName == FName("Mine"))
	{
		bIsClearMine = true;
	}
	else if (SelectedMapName == FName("Hospital"))
	{
		bIsClearHospital = true;
	}

	SaveGameInstance->bIsClearHotel = bIsClearHotel;
	SaveGameInstance->bIsClearMine = bIsClearMine;
	SaveGameInstance->bIsClearHospital = bIsClearHospital;

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("HSGameSaveSlot"), 0);
}

#pragma endregion