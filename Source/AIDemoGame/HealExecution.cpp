// Fill out your copyright notice in the Description page of Project Settings.

#include "HealExecution.h"
#include "MyAttributeSet.h"
#include "AbilitySystemComponent.h"

struct HealStatics {
    DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
    DECLARE_ATTRIBUTE_CAPTUREDEF(BaseHealingPower);

    HealStatics() {
        // Capture the Target's Health attribute. Do not snapshot it, because we want to use the health value at the moment we apply the execution.
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, Health, Target, false);

        // Capture the Source's AttackPower. We do want to snapshot this at the moment we create the GameplayEffectSpec that will execute the damage.
        // (imagine we fire a projectile: we create the GE Spec when the projectile is fired. When it hits the target, we want to use the AttackPower at the
        // moment the projectile was launched, not when it hits).
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, BaseHealingPower, Source, true);
    }
};

HealStatics& Heal() {
    static HealStatics It;
    return It;
}

UHealExecution::UHealExecution(const FObjectInitializer& ObjectInitializer) {
    RelevantAttributesToCapture.Add(Heal().HealthDef);
    RelevantAttributesToCapture.Add(Heal().BaseHealingPowerDef);
}

void UHealExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                            OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const {
    UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
    UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

    AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->AvatarActor : nullptr;
    AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->AvatarActor : nullptr;

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;

    // --------------------------------------------------------------------------------------------

    float Health = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Heal().HealthDef, EvaluationParameters, Health);

    float HealingPower = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Heal().BaseHealingPowerDef, EvaluationParameters, HealingPower);

    float HealingDone = HealingPower;

    if (HealingDone > 0.f) {
        OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(Heal().HealthProperty, EGameplayModOp::Additive, HealingDone));
    }
}
