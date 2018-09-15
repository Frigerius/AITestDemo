// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GABaseAIController.h"
#include "UtilityAIController.generated.h"

/**
 *
 */
UCLASS()
class AIDEMOGAME_API AUtilityAIController : public AGABaseAIController {
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxDistToCamp = 1500.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxRange = 900.f;

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
    float GetDistHome();

    UFUNCTION(BlueprintCallable)
    float GetDistTarget();
    UPROPERTY(BlueprintReadOnly)
    FVector StartSpot;
    UFUNCTION(BlueprintCallable)
    float NeedHeal();
    UPROPERTY(BlueprintReadOnly)
    class AEnemyCharacter* MyActor;
    UFUNCTION(BlueprintCallable)
    float GetTargetDistToHome();
    UFUNCTION(BlueprintCallable)
    float ShouldGoHome();
    UFUNCTION(BlueprintCallable)
    float ShouldMoveToTarget();
    UFUNCTION(BlueprintCallable)
    bool CanReachTarget();

private:
    UPROPERTY(EditAnywhere)
    float HealEdge = 70.f;
    UPROPERTY(EditAnywhere)
    TSubclassOf<class UGameplayEffect> HealCDEffect;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameData, meta = (AllowPrivateAccess = "true"))
    float CurHealth;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameData, meta = (AllowPrivateAccess = "true"))
    float MaxHealth;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameData, meta = (AllowPrivateAccess = "true"))
    float MaxRangeSqrt;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameData, meta = (AllowPrivateAccess = "true"))
    float MaxDistToCampSqrt;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameData, meta = (AllowPrivateAccess = "true"))
    float CurDistHome;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameData, meta = (AllowPrivateAccess = "true"))
    float CurTargetDistMyHome;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameData, meta = (AllowPrivateAccess = "true"))
    int CurHealCDStackCount;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameData, meta = (AllowPrivateAccess = "true"))
    float CurHealthPerc;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameData, meta = (AllowPrivateAccess = "true"))
    float MyE;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameData, meta = (AllowPrivateAccess = "true"))
    float CurDistTarget;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameData, meta = (AllowPrivateAccess = "true"))
    bool CurHasTarget;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameData, meta = (AllowPrivateAccess = "true"))
    float MaxReachableTargetSqrt;
};
