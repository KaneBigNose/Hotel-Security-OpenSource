// Copyright Epic Games, Inc. All Rights Reserved.

#include "Hotel_SecurityGameMode.h"
#include "Hotel_SecurityCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHotel_SecurityGameMode::AHotel_SecurityGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
