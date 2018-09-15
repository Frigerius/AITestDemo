// Fill out your copyright notice in the Description page of Project Settings.

#include "MyStateMachine.h"
#include "MyState.h"
#include "FSM/SuperState.h"

void UMyStateMachine::AddState(UMyState* State) {
    States.Add(State);
    State->SetStateMachine(this);
    if (States.Num() < 2) {
        SetInitialState(State);
        SetCurrentState(State);
    }
    if (USuperState* SuperState = Cast<USuperState>(State)) {
        SuperState->StateChanged.AddDynamic(this, &UMyStateMachine::SuperStateHasStateChanged);
    }
}

void UMyStateMachine::SetInitialState(UMyState* State) {
    InitialState = State;
}

void UMyStateMachine::SetCurrentState(UMyState* State) {
    CurrentState = State;
}

void UMyStateMachine::Execute() {
    if (!CurrentState) {
        CurrentState = InitialState;
        bStateChanged = true;
    }
    if (bStateChanged) {
        bStateChanged = false;
        StateChanged.Broadcast(CurrentState->GetName());
    }
    UMyState* result = CurrentState->Execute();
    if (result != nullptr) {
        SetCurrentState(result);
        bStateChanged = true;
    }
}

UMyState* UMyStateMachine::GetCurrentState() {
    return CurrentState;
}

UMyState* UMyStateMachine::GetInitialState() {
    return InitialState;
}

void UMyStateMachine::SuperStateHasStateChanged(FString Name) {
    StateChanged.Broadcast(Name);
}
