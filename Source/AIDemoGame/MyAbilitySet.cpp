// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAbilitySet.h"
#include "AbilitySystemComponent.h"

void UMyAbilitySet::GiveAbilities(UAbilitySystemComponent* AbilitySystemComponent) const {
    for (const FMyAbilityBindInfo& BindInfo : Abilities) {
        if (BindInfo.GameplayAbilityClass) {
            AbilitySystemComponent->GiveAbility(
                FGameplayAbilitySpec(BindInfo.GameplayAbilityClass->GetDefaultObject<UGameplayAbility>(), 1, (int32)BindInfo.Command));
        }
    }
}
