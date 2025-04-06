// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Delegates/DelegateCombinations.h"
#include "HSGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStageClearDelegate);

UCLASS()
class HOTEL_SECURITY_API UHSGameInstance : public UGameInstance
{
	GENERATED_BODY()

#pragma region Base

public:
	UHSGameInstance();

protected:
	virtual void Init() override;

#pragma endregion

#pragma region Language

public:
	FName GetSelectedLanguage() { return SelectedLanguage; }
	void SetSelectedLanguage(FName LanguageName) { SelectedLanguage = LanguageName; }

protected:
	FName SelectedLanguage = FName("English");

#pragma endregion

#pragma region Widget

public:
	class UUserWidget* GetCurrentOpenWidget() { return CurrentOpenWidget; }
	void SetCurrentOpenWidget(UUserWidget* CurrentWidget) { CurrentOpenWidget = CurrentWidget; }

protected:
	UPROPERTY()
	class UUserWidget* CurrentOpenWidget;

#pragma endregion

#pragma region Map

public:
	FName GetSelectedMapName() { return SelectedMapName; }
	void SetSelectedMapName(FName MapName) { SelectedMapName = MapName; }

protected:
	FName SelectedMapName = FName("None");

#pragma endregion

#pragma region Stage Clear

public:
	UFUNCTION()
	void CreateStageClearWidget();

protected:
	UPROPERTY()
	TSubclassOf<class UHSStageClearWidget> StageClearClass;

	UPROPERTY()
	class UHSStageClearWidget* StageClearWidget;

#pragma endregion

#pragma region Save

protected:
	void LoadGameSaveData();
	void SaveGameSaveData();

public:
	UPROPERTY()
	bool bIsClearHotel = false;

	UPROPERTY()
	bool bIsClearMine = false;

	UPROPERTY()
	bool bIsClearHospital = false;

#pragma endregion

#pragma region Delegate

public:
	FStageClearDelegate StageClearDelegate;

#pragma endregion

};