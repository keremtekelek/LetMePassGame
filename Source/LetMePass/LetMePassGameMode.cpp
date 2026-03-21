// Copyright Epic Games, Inc. All Rights Reserved.

#include "LetMePassGameMode.h"
#include "Public/LetMePassCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALetMePassGameMode::ALetMePassGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/01_MyContent/Blueprints/Characters/BP_MainCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
