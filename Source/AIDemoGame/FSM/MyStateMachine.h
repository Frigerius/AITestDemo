// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Containers/Array.h"
#include "MyStateMachine.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStateChanged, FString, Name);

class UMyState;
/**
 *
 */
UCLASS(Blueprintable)
class AIDEMOGAME_API UMyStateMachine : public UObject {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void AddState(UMyState* State);
    UFUNCTION(BlueprintCallable)
    void SetInitialState(UMyState* State);
    UFUNCTION(BlueprintCallable)
    void SetCurrentState(UMyState* State);
    UFUNCTION(BlueprintCallable)
    void Execute();
    UFUNCTION(BlueprintCallable)
    UMyState* GetCurrentState();
    UMyState* GetInitialState();

    UPROPERTY(BlueprintAssignable)
    FStateChanged StateChanged;

private:
    UPROPERTY()
    TArray<UMyState*> States;
    UPROPERTY()
    UMyState* InitialState;
    UPROPERTY()
    UMyState* CurrentState;
    UFUNCTION()
    void SuperStateHasStateChanged(FString Name);
    UPROPERTY()
    bool bStateChanged = false;
};
