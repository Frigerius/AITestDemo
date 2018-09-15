// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseBehavior.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class AIDEMOGAME_API UBaseBehavior : public UObject {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void Execute();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    float GetScore();
};
