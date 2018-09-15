// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyTransition.generated.h"

DECLARE_DELEGATE_RetVal(bool, FTransitionCondition)

    class UMyState;
/**
 *
 */
UCLASS(Blueprintable)
class AIDEMOGAME_API UMyTransition : public UObject {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    bool CheckCondition();
    UFUNCTION(BlueprintCallable)
    void SetTargetState(UMyState* State);
    UFUNCTION(BlueprintCallable)
    UMyState* GetTargetState();
    FTransitionCondition Condition;

private:
    UMyState* TargetState;
};
