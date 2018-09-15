// Fill out your copyright notice in the Description page of Project Settings.

#include "UtilityAIController.h"
#include "EnemyCharacter.h"
#include "GameplayEffect.h"

void AUtilityAIController::BeginPlay() {
    StartSpot = GetPawn()->GetActorLocation();
    MyActor = Cast<AEnemyCharacter>(GetPawn());
    CurHealth = MyActor->AttributeSet->Health;
    MaxHealth = MyActor->AttributeSet->MaxHealth;
    MaxRangeSqrt = MaxRange * MaxRange;
    MaxDistToCampSqrt = MaxDistToCamp * MaxDistToCamp;
    MyE = 2.718 * 0.45;
    CurHasTarget = false;
    MaxReachableTargetSqrt = (MaxDistToCamp + MaxRange) * (MaxDistToCamp + MaxRange);
    Super::BeginPlay();
}

void AUtilityAIController::Tick(float DeltaTime) {
    CurHealth = MyActor->AttributeSet->Health;
    CurDistHome = FVector::DistSquaredXY(GetPawn()->GetActorLocation(), StartSpot);
    AActor* Target = GetTarget();
    CurHasTarget = Target != nullptr;
    if (CurHasTarget) {
        CurTargetDistMyHome = FVector::DistSquared(Target->GetActorLocation(), StartSpot);
        CurDistTarget = FVector::DistSquared(Target->GetActorLocation(), GetPawn()->GetActorLocation());
        if (CurTargetDistMyHome > MaxReachableTargetSqrt) {
            SetTarget(nullptr);
            CurHasTarget = false;
            CurTargetDistMyHome = TNumericLimits<float>::Max();
            CurDistTarget = TNumericLimits<float>::Max();
        }
    } else {
        CurTargetDistMyHome = TNumericLimits<float>::Max();
        CurDistTarget = TNumericLimits<float>::Max();
    }
    CurHealCDStackCount = MyActor->GetAbilitySystemComponent()->GetGameplayEffectCount(HealCDEffect, nullptr);
    CurHealthPerc = CurHealth / MaxHealth;
    Super::Tick(DeltaTime);
}

float AUtilityAIController::GetDistHome() {
    return CurDistHome;
}

float AUtilityAIController::GetDistTarget() {
    return CurDistTarget;
}

float AUtilityAIController::NeedHeal() {
    if (CurHealth < MaxHealth) {
        return (1 - CurHealCDStackCount) * (1 / (1 + (FMath::Pow(MyE, (CurHealthPerc * 100) - HealEdge))));
    }
    return 0;
}

float AUtilityAIController::GetTargetDistToHome() {
    return CurTargetDistMyHome;
}

float AUtilityAIController::ShouldGoHome() {
    if (CurDistHome <= 150) {
        return 0;
    } else {
        if (CurHealthPerc <= .3f && CurHealCDStackCount > 0) {
            return 1 - FMath::Clamp((FMath::Pow(MaxDistToCampSqrt - CurDistHome, 3) / FMath::Pow(MaxDistToCampSqrt, 3)), 0.f, 1.f);
        }
        if (!CurHasTarget)
            return 1;
        // return 1 - FMath::Pow((MaxReachableTargetSqrt - GetTargetDistToHome()), 3) / FMath::Pow(MaxReachableTargetSqrt, 3);
        return FMath::Clamp(FMath::Pow(GetTargetDistToHome() / MaxReachableTargetSqrt, 3), 0.f, 1.f);
    }
}

float AUtilityAIController::ShouldMoveToTarget() {
    if (!CurHasTarget)
        return 0;
    if (GetDistHome() >= MaxDistToCampSqrt)
        return 0;
    return GetDistTarget() > MaxRangeSqrt && CanReachTarget() && (CurHealthPerc > .3f) ? 1 : 0;
}

bool AUtilityAIController::CanReachTarget() {
    if (CurHasTarget) {
        return CurTargetDistMyHome <= MaxReachableTargetSqrt;
    }
    return false;
}
