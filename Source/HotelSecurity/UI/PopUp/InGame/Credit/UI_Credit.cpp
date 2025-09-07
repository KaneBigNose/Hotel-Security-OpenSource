// Made by LSH

#include "UI/PopUp/InGame/Credit/UI_Credit.h"
#include "Components/ScrollBox.h"
#include "GameSystem/GameInstance/HSGameInstance.h"

#pragma region Base

void UUI_Credit::NativeConstruct()
{
	Super::NativeConstruct();

	const float MoveSpeed = 50;
	float CurrentOffset = 0;

	FTimerHandle CreditHandle;
	GetWorld()->GetTimerManager().SetTimer(CreditHandle, [this, MoveSpeed, CurrentOffset]() mutable
		{
			CurrentOffset += MoveSpeed * 0.016f;
			CreditScroll->SetScrollOffset(CurrentOffset);
		}, 0.16f, true);
}

#pragma endregion

#pragma region Input

void UUI_Credit::InputWidget_Enter()
{
	UHSGameInstance* GameInstance = GetWorld()->GetGameInstance<UHSGameInstance>();
	GameInstance->OpenMap(EMapType::MainMenu);
}

void UUI_Credit::InputWidget_ESC()
{
	UHSGameInstance* GameInstance = GetWorld()->GetGameInstance<UHSGameInstance>();
	GameInstance->OpenMap(EMapType::MainMenu);
}

#pragma endregion