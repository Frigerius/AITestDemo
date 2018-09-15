// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AIDemoGameGameMode.h"
#include "AIDemoGamePlayerController.h"
#include "AIDemoGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAIDemoGameGameMode::AAIDemoGameGameMode() {
    // use our custom PlayerController class
    PlayerControllerClass = AAIDemoGamePlayerController::StaticClass();

    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/MyChar"));
    if (PlayerPawnBPClass.Class != NULL) {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}