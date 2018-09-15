// Fill out your copyright notice in the Description page of Project Settings.

#include "MyState.h"
#include "MyTransition.h"
#include "MyStateMachine.h"

void UMyState::AddTranstition(UMyTransition* Transition) {
    Transitions.Push(Transition);
}

UMyState* UMyState::Execute_Implementation() {
    return nullptr;
}

// void UMyState::Init(UMyStateMachine * Statmachine, const FString & Name)
//{
//	this->StateMachine = StateMachine;
//	//this->Name = Name;
//}

void UMyState::SetStateMachine(UMyStateMachine* StateMachine) {
    this->StateMachine = StateMachine;
}

UMyStateMachine* UMyState::GetStateMachine() {
    return StateMachine;
}

// FString UMyState::GetName() const
//{
//	return Name;
//}
//
// void UMyState::SetName(const FString& NewName)
//{
//	Name = NewName;
//}

UMyState* UMyState::FindNextState() {
    for (UMyTransition* Transition : Transitions) {
        if (Transition->CheckCondition()) {
            return Transition->GetTargetState();
        }
    }
    return nullptr;
}

void UMyState::KillExecution_Implementation() {}
