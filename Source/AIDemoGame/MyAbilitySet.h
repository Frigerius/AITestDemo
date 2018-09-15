// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Templates/SubclassOf.h"
#include "Engine/DataAsset.h"
#include "Abilities/GameplayAbility.h"
#include "MyAbilitySet.generated.h"

class UAbilitySystemComponent;

/**
 *
 */

UENUM(BlueprintType)
namespace EMyInputBinds {
enum Spells {
    Fireball = 0 UMETA(DisplayName = "Fireball"),
    Heal = 1 UMETA(DisplayName = "Heal"),

};
}

USTRUCT()
struct AIDEMOGAME_API FMyAbilityBindInfo {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = BindInfo)
    TEnumAsByte<EMyInputBinds::Spells> Command;

    UPROPERTY(EditAnywhere, Category = BindInfo)
    TSubclassOf<UGameplayAbility> GameplayAbilityClass;
};

UCLASS()
class AIDEMOGAME_API UMyAbilitySet : public UDataAsset {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = AbilitySet)
    TArray<FMyAbilityBindInfo> Abilities;

public:
    void GiveAbilities(UAbilitySystemComponent* AbilitySystemComponent) const;
};
