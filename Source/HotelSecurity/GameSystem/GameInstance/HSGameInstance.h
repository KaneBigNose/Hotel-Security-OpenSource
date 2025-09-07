// Made by LSH

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Delegates/DelegateCombinations.h"
#include "HSGameInstance.generated.h"

#pragma region Declare

UENUM(BlueprintType)
enum class EMapType : uint8
{
	None		UMETA(DisplayName = "None"),
	MainMenu	UMETA(DisplayName = "MainMenu"),
	Hotel		UMETA(DisplayName = "Hotel"),
	Mine		UMETA(DisplayName = "Mine"),
	Hospital	UMETA(DisplayName = "Hospital"),
	OldMotel	UMETA(DisplayName = "OldMotel")
};

UENUM(BlueprintType)
enum class ELanguageType : uint8
{
	English		UMETA(DisplayName = "English"),
	Korean		UMETA(DisplayName = "Korean")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStageClear);

#pragma endregion

UCLASS()
class HOTEL_SECURITY_API UHSGameInstance : public UGameInstance
{
	GENERATED_BODY()

#pragma region Base

public:
	UHSGameInstance();

protected:
	virtual void Init() override;
	virtual void Shutdown() override;

#pragma endregion

#pragma region Map

public:
	void OpenMap(const EMapType& MapType);

public:
	static EMapType SelectedMap;
	static ELanguageType SelectedLanguage;

protected:
	UPROPERTY()
	TSubclassOf<class UUI_PopUp_Base> LoadingClass;

#pragma endregion

#pragma region Stage Clear

public:
	FStageClear StageClear;

protected:
	UFUNCTION()
	void StageClearFunc();

protected:
	UPROPERTY()
	TSubclassOf<class UUI_PopUp_Base> StageClearClass;

	UPROPERTY()
	TSubclassOf<class UUI_PopUp_Base> CreditClass;

#pragma endregion

};