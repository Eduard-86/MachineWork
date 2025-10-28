// Copyright Epic Games, Inc. All Rights Reserved.

#include "MachineWorkGameMode.h"
#include "MachineWorkCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMachineWorkGameMode::AMachineWorkGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
