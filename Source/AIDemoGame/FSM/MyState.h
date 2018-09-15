// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyState.generated.h"

class UMyTransition;
class UMyStateMachine;
class UMyState;

/**
 *
 */

UCLASS(Blueprintable)
class AIDEMOGAME_API UMyState : public UObject {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void AddTranstition(UMyTransition* Transition);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    UMyState* Execute();
    // UFUNCTION(BlueprintCallable)
    //	void Init(UMyStateMachine* Statmachine, const FString& Name);
    UFUNCTION(BlueprintCallable)
    void SetStateMachine(UMyStateMachine* StateMachine);
    UFUNCTION(BlueprintCallable)
    UMyStateMachine* GetStateMachine();
    // UFUNCTION(BlueprintCallable)
    //	FString GetName() const;
    // UFUNCTION(BlueprintCallable)
    //	void SetName(const FString& NewName);
    UFUNCTION(BlueprintCallable)
    UMyState* FindNextState();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void KillExecution();

protected:
    UPROPERTY()
    TArray<UMyTransition*> Transitions;
    UPROPERTY()
    UMyStateMachine* StateMachine;
    // FString Name;
};
