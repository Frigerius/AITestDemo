// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GABaseAIController.h"
#include "GameplayAbility.h"
#include "GameplayEffect.h"
#include "FSMAIController.generated.h"

class UMyStateMachine;
class UMyTransition;
class USuperState;
class UMyState;
class AEnemyCharacter;
class UMyAttributeSet;

/**
 *
 */
UCLASS()
class AIDEMOGAME_API AFSMAIController : public AGABaseAIController {
    GENERATED_BODY()
public:
    void BeginPlay() override;
    UFUNCTION(BlueprintCallable)
    UMyStateMachine* GetStateMachine();
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UGameplayAbility> HealAbility;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UGameplayAbility> FireAbility;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UGameplayEffect> HealCDEffect;
    virtual void Tick(float DeltaTime) override;
    virtual void PostInitializeComponents() override;
    virtual void PostRegisterAllComponents() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxDistHome = 1500.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxRangeToTarget = 900.f;
    bool AreHPTooLow();
    bool IsTargetInRange();
    bool MaxDistHomeReached();
    bool IsTargetNotInRangeAndMaxDistHomeReached();
    bool IsAtHome();
    bool CanHeal();

private:
    UPROPERTY()
    UMyStateMachine* StateMachine;
    UPROPERTY()
    FVector StartPosition;
    UPROPERTY()
    AEnemyCharacter* MeEnemy;
    UPROPERTY()
    UMyAttributeSet* Attributes;

    USuperState* CreateNoTargetStates();
    USuperState* CreateHasTargetStates();
    UMyTransition* MakeTransition(UMyState* Source, UMyState* Target);
};
