// Copyright Epic Games, Inc. All Rights Reserved.

#include "The_AscendanceGameMode.h"
#include "The_AscendanceCharacter.h"
#include "UObject/ConstructorHelpers.h"

AThe_AscendanceGameMode::AThe_AscendanceGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
