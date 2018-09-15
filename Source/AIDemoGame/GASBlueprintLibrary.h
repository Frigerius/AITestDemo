// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GASBlueprintLibrary.generated.h"

/**
 *
 */
UCLASS()
class AIDEMOGAME_API UGASBlueprintLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, Category = AbilitySystem)
    static void GenerateEffectSpecs(UPARAM(ref) FGASEffectApplicationContainer& Container, AActor* Source, float LevelOverride = 0.f, int32 StackOverride = 0);

    UFUNCTION(BlueprintCallable, Category = AbilitySystem)
    static void AddHitResult(UPARAM(ref) FGASEffectApplicationContainer& Container, FHitResult HitResult);

    UFUNCTION(BlueprintCallable, Category = AbilitySystem)
    static TArray<FActiveGameplayEffectHandle> ApplyEffectApplicationContainerToTarget(UPARAM(ref) FGASEffectApplicationContainer& Container, AActor* Target);
};
