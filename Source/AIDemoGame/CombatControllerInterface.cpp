// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatControllerInterface.h"
#include "GameFramework/Actor.h"

// Add default functionality here for any ICombatControllerInterface functions that are not pure virtual.
AActor* ICombatControllerInterface::GetTarget() const {
    return nullptr;
}

AActor* ICombatControllerInterface::GetLastDmgCauser() const {
    return nullptr;
}

void ICombatControllerInterface::SetLastDmgCauser(AActor* DmgCauser) {}
