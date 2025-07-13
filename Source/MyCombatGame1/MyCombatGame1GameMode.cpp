// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyCombatGame1GameMode.h"
#include "MyCombatGame1Character.h"
#include "UObject/ConstructorHelpers.h"

AMyCombatGame1GameMode::AMyCombatGame1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
