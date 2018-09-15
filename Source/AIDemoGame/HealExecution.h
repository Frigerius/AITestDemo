// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "HealExecution.generated.h"

/**
 *
 */
UCLASS()
class AIDEMOGAME_API UHealExecution : public UGameplayEffectExecutionCalculation {
    GENERATED_BODY()

    UHealExecution(const FObjectInitializer& ObjectInitializer);
    virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                        OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
