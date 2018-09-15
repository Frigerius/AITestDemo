// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyState.h"
#include "GameplayAbility.h"
#include "MyTransition.h"

#include "StateCollection.generated.h"

class AFSMAIController;
class AEnemyCharacter;
class AActor;

/**
 *
 */
UCLASS()
class AIDEMOGAME_API UStateCollection : public UMyState {
    GENERATED_BODY()
};

UCLASS()
class AIDEMOGAME_API UCastSpellState : public UMyState {
    GENERATED_BODY()

public:
    void SetAbilitieToCast(TSubclassOf<UGameplayAbility> Ability);
    void SetAIController(AFSMAIController* Controller);
    virtual UMyState* Execute_Implementation() override;

private:
    UPROPERTY()
    TSubclassOf<UGameplayAbility> AbilitieToCast;
    UPROPERTY()
    AFSMAIController* MyAIController;
    UPROPERTY()
    AEnemyCharacter* MyCharacter;
};

UCLASS()
class AIDEMOGAME_API UMoveToState : public UMyState {
    GENERATED_BODY()
public:
    void SetTarget(AActor* Target);
    void SetTarget(FVector Target);
    void SetKillOnChange(bool bKill);
    bool GetKillOnChange();
    virtual UMyState* Execute_Implementation() override;
    void SetAIController(AFSMAIController* Controller);
    virtual void KillExecution_Implementation() override;

private:
    UPROPERTY()
    FVector VTarget;
    UPROPERTY()
    AActor* ATarget;
    UPROPERTY()
    AFSMAIController* MyAIController;
    bool bKillOnChange = true;
};

UCLASS()
class AIDEMOGAME_API UIdleState : public UMyState {
    GENERATED_BODY()

public:
    virtual UMyState* Execute_Implementation() override;
};

UCLASS()
class AIDEMOGAME_API URemoveTargetState : public UMyState {
    GENERATED_BODY()
public:
    void SetAIController(AFSMAIController* Controller);
    virtual UMyState* Execute_Implementation() override;

private:
    UPROPERTY()
    AFSMAIController* MyAIController;
};

UCLASS()
class AIDEMOGAME_API UMoveToTargetState : public UMyState {
    GENERATED_BODY()
public:
    virtual UMyState* Execute_Implementation() override;
    void SetAIController(AFSMAIController* Controller);
    virtual void KillExecution_Implementation() override;

private:
    UPROPERTY()
    AFSMAIController* MyAIController;
};
