// Made by LSH

#include "UI/MainMenu/Description/HSDescriptionWidget_Explain.h"
#include "UI/MainMenu/Description/HSDescriptionWidget_Keyboard.h"
#include "UI/MainMenu/HSMainMenu.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameInstance/HSGameInstance.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

void UHSDescriptionWidget_Explain::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	NextButton->OnClicked.AddDynamic(this, &ThisClass::ClickNextButton);
}

#pragma endregion

#pragma region Click

void UHSDescriptionWidget_Explain::ClickNextButton()
{
	TArray<UUserWidget*> FoundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHSDescriptionWidget_Keyboard::StaticClass(), false);

	Cast<UHSDescriptionWidget_Keyboard>(FoundWidgets[0])->AddToViewport();

	RemoveFromParent();

	UHSGameInstance* GameInstance = Cast<UHSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->SetCurrentOpenWidget(Cast<UHSDescriptionWidget_Keyboard>(FoundWidgets[0]));
}

#pragma endregion

#pragma region Interface

void UHSDescriptionWidget_Explain::EscapeCurrentWidget()
{
	TArray<UUserWidget*> FoundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHSMainMenu::StaticClass(), false);

	Cast<UHSMainMenu>(FoundWidgets[0])->AddToViewport();

	RemoveFromParent();
}

void UHSDescriptionWidget_Explain::EnterCurrentWidget()
{
	ClickNextButton();
}

#pragma endregion