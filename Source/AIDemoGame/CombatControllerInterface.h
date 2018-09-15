// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UCombatControllerInterface : public UInterface {
    GENERATED_BODY()
};

class AActor;

/**
 *
 */
class AIDEMOGAME_API ICombatControllerInterface {
    GENERATED_BODY()

    // Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual AActor* GetTarget() const;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual AActor* GetLastDmgCauser() const;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual void SetLastDmgCauser(AActor* DmgCauser);
};
