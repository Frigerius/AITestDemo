// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CombatControllerInterface.h"
#include "GABaseAIController.generated.h"

class AActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDmgCauserChanged, AActor*, DmgCauser);
/**
 *
 */
UCLASS()
class AIDEMOGAME_API AGABaseAIController : public AAIController, public ICombatControllerInterface {
    GENERATED_BODY()
public:
    // Begin ICombatControllerInterface
    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual AActor* GetTarget() const override;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual AActor* GetLastDmgCauser() const override;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual void SetLastDmgCauser(AActor* DmgCauser) override;
    // End ICombatControllerInterface

    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual void SetTarget(AActor* Target);

    UPROPERTY(BlueprintAssignable, Category = "Combat")
    FDmgCauserChanged DamageCauserChanged;

protected:
    AActor* MyTarget;
    AActor* LastDmgCauser;
};
