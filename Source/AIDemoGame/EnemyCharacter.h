// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "MyAttributeSet.h"

#include "EnemyCharacter.generated.h"

UCLASS()
class AIDEMOGAME_API AEnemyCharacter : public ACharacter, public IAbilitySystemInterface {
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AEnemyCharacter();

    UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; };

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UMyAttributeSet* AttributeSet;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    class UMyAbilitySet* AbilitySet;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
    UAbilitySystemComponent* AbilitySystem;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
