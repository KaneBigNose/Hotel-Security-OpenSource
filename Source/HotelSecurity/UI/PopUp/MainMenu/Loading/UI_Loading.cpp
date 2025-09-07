// Made by LSH

#include "UI/PopUp/MainMenu/Loading/UI_Loading.h"
#include "UI/Controller/UI_Controller.h"
#include "GameSystem/GameSave/HSSave_Tutorial.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

void UUI_Loading::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(Disappear);
}

void UUI_Loading::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	CurrentTime += InDeltaTime;

	if (CurrentTime < MaxTime)
	{
		return;
	}

	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->CloseStrongPopUpWidget(EInputModeType::GameOnly);

	UHSSave_Tutorial* Save_Tutorial = Cast<UHSSave_Tutorial>(UGameplayStatics::LoadGameFromSlot(TEXT("HSSave_Tutorial"), 0));
	if (Save_Tutorial->LoadTutorialData())
	{
		UICon->OpenPopUpWidget(TutorialClass);
	}

	Save_Tutorial->SaveTutorialData();
}

#pragma endregion

#pragma region Input

void UUI_Loading::InputWidget_ESC()
{

}

#pragma endregion