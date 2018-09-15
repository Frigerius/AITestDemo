// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyState.h"
#include "Containers/Array.h"
#include "SuperState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChildStateChanged, FString, Name);
/**
 *
 */
UCLASS()
class AIDEMOGAME_API USuperState : public UMyState {
    GENERATED_BODY()

public:
    virtual UMyState* Execute_Implementation() override;

    void AddState(UMyState* State);
    void SetInitialState(UMyState* State);
    void SetCurrentState(UMyState* State);

    UPROPERTY(BlueprintAssignable)
    FChildStateChanged StateChanged;

private:
    UPROPERTY()
    UMyState* InitialState;
    UPROPERTY()
    UMyState* CurrentState;
    UPROPERTY()
    TArray<UMyState*> States;
    UFUNCTION()
    void SuperStateHasStateChanged(FString Name);
    UPROPERTY()
    bool bStateChanged = false;
};
