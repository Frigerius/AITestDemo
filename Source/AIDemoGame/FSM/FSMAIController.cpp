// Fill out your copyright notice in the Description page of Project Settings.

#include "FSMAIController.h"
#include "MyStateMachine.h"
#include "MyTransition.h"
#include "Engine.h"
#include "FSM/SuperState.h"
#include "FSM/StateCollection.h"
#include "MyState.h"
#include "GameFramework/Pawn.h"
#include "EnemyCharacter.h"
#include "MyAttributeSet.h"
#include "MyAbilitySet.h"

void AFSMAIController::BeginPlay() {
    Super::BeginPlay();

    StateMachine = NewObject<UMyStateMachine>(this, UMyStateMachine::StaticClass());
    StartPosition = GetPawn()->GetActorLocation();
    MeEnemy = Cast<AEnemyCharacter>(GetPawn());
    Attributes = MeEnemy->AttributeSet;
    USuperState* NoTarget = CreateNoTargetStates();
    USuperState* HasTarget = CreateHasTargetStates();

    UCastSpellState* Heal = NewObject<UCastSpellState>(StateMachine, UCastSpellState::StaticClass(), FName("Heal"));
    Heal->SetStateMachine(StateMachine);
    Heal->SetAbilitieToCast(HealAbility);
    Heal->SetAIController(this);

    StateMachine->AddState(NoTarget);
    StateMachine->AddState(HasTarget);
    StateMachine->AddState(Heal);
    MakeTransition(NoTarget, HasTarget)->Condition.BindLambda([me = this]() { return me->GetTarget() != nullptr; });
    MakeTransition(HasTarget, NoTarget)->Condition.BindLambda([me = this]() { return me->GetTarget() == nullptr; });
    MakeTransition(NoTarget, Heal)->Condition.BindLambda([=]() { return Attributes->Health < Attributes->MaxHealth && CanHeal(); });
    MakeTransition(HasTarget, Heal)->Condition.BindLambda([=]() { return CanHeal() && AreHPTooLow(); });
    MakeTransition(Heal, HasTarget)->Condition.BindLambda([=]() { return GetTarget() != nullptr; });
    MakeTransition(Heal, NoTarget)->Condition.BindLambda([=]() { return GetTarget() == nullptr; });
}

UMyStateMachine* AFSMAIController::GetStateMachine() {
    return StateMachine;
}

void AFSMAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    StateMachine->Execute();
}

void AFSMAIController::PostInitializeComponents() {
    Super::PostInitializeComponents();
}

void AFSMAIController::PostRegisterAllComponents() {
    Super::PostRegisterAllComponents();
}

USuperState* AFSMAIController::CreateNoTargetStates() {
    USuperState* NoTargetState = NewObject<USuperState>(StateMachine, USuperState::StaticClass(), FName("NoTarget - SuperState"));
    UIdleState* Idle = NewObject<UIdleState>(NoTargetState, UIdleState::StaticClass(), FName("Idle"));
    UMoveToState* MoveHome = NewObject<UMoveToState>(NoTargetState, UMoveToState::StaticClass(), FName("MoveHome"));
    // NoTargetState Init
    NoTargetState->AddState(Idle);
    NoTargetState->AddState(MoveHome);

    // Idle Init
    MakeTransition(Idle, MoveHome)->Condition.BindLambda([me = this]() { return !me->IsAtHome(); });
    // MoveHomeInit
    MoveHome->SetTarget(StartPosition);
    MoveHome->SetAIController(this);
    MoveHome->SetKillOnChange(false);
    MakeTransition(MoveHome, Idle)->Condition.BindUObject(this, &AFSMAIController::IsAtHome);

    return NoTargetState;
}

USuperState* AFSMAIController::CreateHasTargetStates() {
    USuperState* HasTargetState = NewObject<USuperState>(StateMachine, USuperState::StaticClass(), FName("HasTarget - SuperState"));
    UCastSpellState* AttackState = NewObject<UCastSpellState>(HasTargetState, UCastSpellState::StaticClass(), FName("Fire"));
    UMoveToTargetState* MoveTo = NewObject<UMoveToTargetState>(HasTargetState, UMoveToTargetState::StaticClass(), FName("MoveToTarget"));
    URemoveTargetState* RemoveTarget = NewObject<URemoveTargetState>(HasTargetState, URemoveTargetState::StaticClass(), FName("RemoveTarget"));

    // Init HasTargetState
    HasTargetState->AddState(MoveTo);
    HasTargetState->AddState(AttackState);
    HasTargetState->AddState(RemoveTarget);
    // AttackState Init
    AttackState->SetAbilitieToCast(FireAbility);
    AttackState->SetAIController(this);
    MakeTransition(AttackState, MoveTo)->Condition.BindLambda([me = this]() { return !me->IsTargetInRange(); });
    MakeTransition(AttackState, RemoveTarget)->Condition.BindUObject(this, &AFSMAIController::IsTargetNotInRangeAndMaxDistHomeReached);

    // MoveTo Init
    MoveTo->SetAIController(this);
    MakeTransition(MoveTo, AttackState)->Condition.BindUObject(this, &AFSMAIController::IsTargetInRange);
    MakeTransition(MoveTo, RemoveTarget)->Condition.BindUObject(this, &AFSMAIController::IsTargetNotInRangeAndMaxDistHomeReached);

    // RemoveTarget
    RemoveTarget->SetAIController(this);
    MakeTransition(RemoveTarget, AttackState)->Condition.BindLambda([]() { return true; });

    return HasTargetState;
}

UMyTransition* AFSMAIController::MakeTransition(UMyState* Source, UMyState* Target) {
    UMyTransition* Transition = NewObject<UMyTransition>(Source, UMyTransition::StaticClass());
    Transition->SetTargetState(Target);
    Source->AddTranstition(Transition);
    return Transition;
}

bool AFSMAIController::AreHPTooLow() {
    return Attributes->Health <= 0.5f * Attributes->MaxHealth;
}

bool AFSMAIController::IsTargetInRange() {
    if (GetTarget() == nullptr)
        return false;
    return FVector::DistSquared(GetTarget()->GetActorLocation(), MeEnemy->GetActorLocation()) <= MaxRangeToTarget * MaxRangeToTarget;
}

bool AFSMAIController::MaxDistHomeReached() {
    return FVector::DistSquared(MeEnemy->GetActorLocation(), StartPosition) > MaxDistHome * MaxDistHome;
}

bool AFSMAIController::IsTargetNotInRangeAndMaxDistHomeReached() {
    return !IsTargetInRange() && MaxDistHomeReached();
}

bool AFSMAIController::IsAtHome() {
    return FVector::DistSquaredXY(MeEnemy->GetActorLocation(), StartPosition) <= 625;
}

bool AFSMAIController::CanHeal() {
    return MeEnemy->GetAbilitySystemComponent()->GetGameplayEffectCount(HealCDEffect, nullptr) < 1;
}
