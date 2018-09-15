// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTransition.h"
#include "MyState.h"

bool UMyTransition::CheckCondition() {
    if (Condition.IsBound())
        return Condition.Execute();
    return false;
}

void UMyTransition::SetTargetState(UMyState* State) {
    TargetState = State;
}

UMyState* UMyTransition::GetTargetState() {
    return TargetState;
}
