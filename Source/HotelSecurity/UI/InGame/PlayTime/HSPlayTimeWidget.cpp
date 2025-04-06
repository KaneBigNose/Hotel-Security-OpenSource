// Made by LSH

#include "UI/InGame/PlayTime/HSPlayTimeWidget.h"
#include "Components/TextBlock.h"
#include "System/HSGameMode.h"
#include "Kismet/GameplayStatics.h"

UHSPlayTimeWidget::UHSPlayTimeWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UHSPlayTimeWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HSGamemode = Cast<AHSGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void UHSPlayTimeWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	int32 InGameHour = HSGamemode->GetCurrentHour();
	int32 InGameMinute = HSGamemode->GetCurrentMinute();

	FString TimeString = FString::Printf(TEXT("%02d : %02d"), InGameHour, InGameMinute);
	PlayTimeTextBlock->SetText(FText::FromString(TimeString));
}