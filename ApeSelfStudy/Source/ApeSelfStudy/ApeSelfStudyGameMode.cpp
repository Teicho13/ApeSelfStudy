// Copyright Epic Games, Inc. All Rights Reserved.

#include "ApeSelfStudyGameMode.h"
#include "ApeSelfStudyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AApeSelfStudyGameMode::AApeSelfStudyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
