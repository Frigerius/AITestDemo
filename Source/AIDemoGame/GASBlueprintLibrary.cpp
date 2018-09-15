// Fill out your copyright notice in the Description page of Project Settings.

#include "GASBlueprintLibrary.h"

void UGASBlueprintLibrary::GenerateEffectSpecs(UPARAM(ref) FGASEffectApplicationContainer& Container, AActor* Source, float LevelOverride,
                                               int32 StackOverride) {
    Container.GenerateEffectSpecs(Source, LevelOverride, StackOverride);
}

void UGASBlueprintLibrary::AddHitResult(UPARAM(ref) FGASEffectApplicationContainer& Container, FHitResult HitResult) {
    Container.AddHitResult(HitResult);
}

TArray<FActiveGameplayEffectHandle> UGASBlueprintLibrary::ApplyEffectApplicationContainerToTarget(UPARAM(ref) FGASEffectApplicationContainer& Container,
                                                                                                  AActor* Target) {
    return Container.ApplyEffectApplicationContainerToTarget(Target);
}
