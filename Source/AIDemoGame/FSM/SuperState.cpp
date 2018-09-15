// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperState.h"

void USuperState::AddState(UMyState* State) {
    States.Add(State);
    if (States.Num() < 2) {
        SetInitialState(State);
        SetCurrentState(State);
    }
    if (USuperState* SuperState = Cast<USuperState>(State)) {
        SuperState->StateChanged.AddDynamic(this, &USuperState::SuperStateHasStateChanged);
    }
}

void USuperState::SetInitialState(UMyState* State) {
    InitialState = State;
}

void USuperState::SetCurrentState(UMyState* State) {
    CurrentState = State;
}

void USuperState::SuperStateHasStateChanged(FString Name) {
    StateChanged.Broadcast(Name);
}

UMyState* USuperState::Execute_Implementation() {
    if (!CurrentState) {
        CurrentState = InitialState;
        bStateChanged = true;
    }
    if (bStateChanged) {
        bStateChanged = false;
        StateChanged.Broadcast(CurrentState->GetName());
    }
    UMyState* ExecResult = CurrentState->Execute();
    if (ExecResult != nullptr) {
        CurrentState->KillExecution();
        SetCurrentState(ExecResult);
        bStateChanged = true;
    }
    ExecResult = FindNextState();
    if (ExecResult != nullptr) {
        bStateChanged = true;
        CurrentState->KillExecution();
    }
    return ExecResult;
}
