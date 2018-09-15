// Fill out your copyright notice in the Description page of Project Settings.

#include "StateCollection.h"
#include "FSMAIController.h"
#include "EnemyCharacter.h"
#include "GameFramework/Actor.h"

void UCastSpellState::SetAbilitieToCast(TSubclassOf<UGameplayAbility> Ability) {
    AbilitieToCast = Ability;
}

void UCastSpellState::SetAIController(AFSMAIController* Controller) {
    MyAIController = Controller;
    MyCharacter = Cast<AEnemyCharacter>(MyAIController->GetPawn());
}

UMyState* UCastSpellState::Execute_Implementation() {
    bool bCastSuccess = MyCharacter->GetAbilitySystemComponent()->TryActivateAbilityByClass(AbilitieToCast);

    return FindNextState();
}

void UMoveToState::SetTarget(AActor* Target) {
    ATarget = Target;
}

void UMoveToState::SetTarget(FVector Target) {
    ATarget = nullptr;
    VTarget = Target;
}

void UMoveToState::SetKillOnChange(bool bKill) {
    bKillOnChange = bKill;
}

bool UMoveToState::GetKillOnChange() {
    return bKillOnChange;
}

UMyState* UMoveToState::Execute_Implementation() {
    if (MyAIController->GetMoveStatus() != EPathFollowingStatus::Moving) {
        if (ATarget == nullptr) {
            MyAIController->MoveToLocation(VTarget, 10, false);
        } else {
            MyAIController->MoveToActor(ATarget);
        }
    }
    UMyState* Result = FindNextState();
    if (bKillOnChange && Result != nullptr) {
        MyAIController->StopMovement();
    }
    return Result;
}

void UMoveToState::SetAIController(AFSMAIController* Controller) {
    MyAIController = Controller;
}

void UMoveToState::KillExecution_Implementation() {
    MyAIController->StopMovement();
}

void URemoveTargetState::SetAIController(AFSMAIController* Controller) {
    MyAIController = Controller;
}

UMyState* URemoveTargetState::Execute_Implementation() {
    MyAIController->SetTarget(nullptr);
    return FindNextState();
}

UMyState* UIdleState::Execute_Implementation() {
    return FindNextState();
}

UMyState* UMoveToTargetState::Execute_Implementation() {
    if (MyAIController->GetMoveStatus() != EPathFollowingStatus::Moving) {
        MyAIController->MoveToActor(MyAIController->GetTarget());
    }
    UMyState* Result = FindNextState();
    if (Result != nullptr) {
        MyAIController->StopMovement();
    }
    return Result;
}

void UMoveToTargetState::SetAIController(AFSMAIController* Controller) {
    MyAIController = Controller;
}

void UMoveToTargetState::KillExecution_Implementation() {
    MyAIController->StopMovement();
}
