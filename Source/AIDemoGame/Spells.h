// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spells.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum class Spells : uint8 {
    Fireball = 0 UMETA(DisplayName = "Fireball"),
    Heal = 1 UMETA(DisplayName = "Heal"),

};
