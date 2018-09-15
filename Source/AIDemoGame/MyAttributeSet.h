// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "MyAttributeSet.generated.h"

/**
 *
 */
UCLASS()
class AIDEMOGAME_API UMyAttributeSet : public UAttributeSet {
    GENERATED_BODY()

public:
    UPROPERTY(Category = "Base Attributes | MaxHealth", EditAnywhere, BlueprintReadWrite)
    float MaxHealth;
    UPROPERTY(Category = "Base Attributes | Health", EditAnywhere, BlueprintReadWrite)
    float Health;
    UPROPERTY(Category = "Base Attributes | BaseAttackPower", EditAnywhere, BlueprintReadWrite)
    float BaseAttackPower;
    UPROPERTY(Category = "Base Attributes | BaseHealingPower", EditAnywhere, BlueprintReadWrite)
    float BaseHealingPower;

    virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
    void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
    void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

    static FGameplayAttribute HealthAttribute();
    static FGameplayAttribute MaxHealthAttribute();
    static FGameplayAttribute BaseAttackPowerAttribute();
    static FGameplayAttribute BaseHealingPowerAttribute();
};
