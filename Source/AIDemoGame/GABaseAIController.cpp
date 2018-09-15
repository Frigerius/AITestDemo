// Fill out your copyright notice in the Description page of Project Settings.

#include "GABaseAIController.h"
#include "GameFramework/Actor.h"

AActor* AGABaseAIController::GetTarget() const {
    return MyTarget;
}

AActor* AGABaseAIController::GetLastDmgCauser() const {
    return LastDmgCauser;
}

void AGABaseAIController::SetLastDmgCauser(AActor* DmgCauser) {
    if (DmgCauser != nullptr && LastDmgCauser != DmgCauser) {
        LastDmgCauser = DmgCauser;
        DamageCauserChanged.Broadcast(LastDmgCauser);
    }
    if (MyTarget == nullptr) {
        MyTarget = DmgCauser;
    }
}

void AGABaseAIController::SetTarget(AActor* Target) {
    MyTarget = Target;
}
