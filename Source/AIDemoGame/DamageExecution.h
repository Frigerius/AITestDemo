// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageExecution.generated.h"

/**
 *
 */
UCLASS()
class AIDEMOGAME_API UDamageExecution : public UGameplayEffectExecutionCalculation {
    GENERATED_BODY()

    UDamageExecution(const FObjectInitializer& ObjectInitializer);
    virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                        OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
