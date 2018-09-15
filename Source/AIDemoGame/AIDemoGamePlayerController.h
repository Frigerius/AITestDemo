// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CombatControllerInterface.h"
#include "AIDemoGamePlayerController.generated.h"

UCLASS()
class AAIDemoGamePlayerController : public APlayerController, public ICombatControllerInterface {
    GENERATED_BODY()

public:
    AAIDemoGamePlayerController();
    FString GetTargetName() const;

    // Begin ICombatControllerInterface
    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual class AActor* GetTarget() const override;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual AActor* GetLastDmgCauser() const override;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual void SetLastDmgCauser(AActor* DmgCauser) override;
    // End ICombatControllerInterface
protected:
    /** True if the controlled character should navigate to the mouse cursor. */
    uint32 bMoveToMouseCursor : 1;

    // Begin PlayerController interface
    virtual void PlayerTick(float DeltaTime) override;
    virtual void SetupInputComponent() override;
    // End PlayerController interface

    /** Navigate player to the current mouse cursor location. */
    void MoveToMouseCursor();

    /** Navigate player to the given world location. */
    void SetNewMoveDestination(const FVector DestLocation);

    /** Input handlers for SetDestination action. */
    void OnSetDestinationPressed();
    void OnSetDestinationReleased();

    void AttackEnemy();

private:
    class AEnemyCharacter* Target;
    AActor* LastDmgCauser;
    bool bAutoAttack;
    void SetTarget(class AEnemyCharacter* Target);
    void OnTargetDied(AActor* Actor);
};
