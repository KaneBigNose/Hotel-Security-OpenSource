// Made by LSH

#include "UI/MainMenu/Description/HSDescriptionWidget_Keyboard.h"
#include "UI/MainMenu/Description/HSDescriptionWidget_Explain.h"
#include "UI/MainMenu/HSMainMenu.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameInstance/HSGameInstance.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

void UHSDescriptionWidget_Keyboard::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PreviousButton->OnClicked.AddDynamic(this, &ThisClass::ClickPreviousButton);
	MainMenuButton->OnClicked.AddDynamic(this, &ThisClass::ClickMainMenuButton);
}

#pragma endregion

#pragma region Click

void UHSDescriptionWidget_Keyboard::ClickPreviousButton()
{
	TArray<UUserWidget*> FoundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHSDescriptionWidget_Explain::StaticClass(), false);

	Cast<UHSDescriptionWidget_Explain>(FoundWidgets[0])->AddToViewport();

	RemoveFromParent();
}

void UHSDescriptionWidget_Keyboard::ClickMainMenuButton()
{
	TArray<UUserWidget*> FoundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHSMainMenu::StaticClass(), false);

	Cast<UHSMainMenu>(FoundWidgets[0])->AddToViewport();

	RemoveFromParent();
}

#pragma endregion

#pragma region Interface

void UHSDescriptionWidget_Keyboard::EscapeCurrentWidget()
{
	ClickMainMenuButton();
}

void UHSDescriptionWidget_Keyboard::EnterCurrentWidget()
{
	ClickMainMenuButton();
	UHSGameInstance* GameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->SetCurrentOpenWidget(nullptr);
}

#pragma endregion