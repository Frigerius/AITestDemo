// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemComponent.h"
#include "CombatControllerInterface.h"

void UMyAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const {
    if (Attribute == HealthAttribute()) {
        NewValue = FMath::Clamp(NewValue, 0.f, MaxHealth);
    }
}

void UMyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) {}

void UMyAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) {
    UAbilitySystemComponent* Source = Data.EffectSpec.GetContext().GetOriginalInstigatorAbilitySystemComponent();

    if (HealthAttribute() == Data.EvaluatedData.Attribute) {
        // Get the Target actor
        AActor* DamagedActor = nullptr;
        AController* DamagedController = nullptr;
        if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid()) {
            DamagedActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
            DamagedController = Data.Target.AbilityActorInfo->PlayerController.Get();
            if (DamagedController == nullptr && DamagedActor != nullptr) {
                if (APawn* Pawn = Cast<APawn>(DamagedActor)) {
                    DamagedController = Pawn->GetController();
                }
            }
        }

        // Get the Source actor
        AActor* AttackingActor = nullptr;
        AController* AttackingController = nullptr;
        AController* AttackingPlayerController = nullptr;
        if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid()) {
            AttackingActor = Source->AbilityActorInfo->AvatarActor.Get();
            AttackingController = Source->AbilityActorInfo->PlayerController.Get();
            AttackingPlayerController = Source->AbilityActorInfo->PlayerController.Get();
            if (AttackingController == nullptr && AttackingActor != nullptr) {
                if (APawn* Pawn = Cast<APawn>(AttackingActor)) {
                    AttackingController = Pawn->GetController();
                }
            }
        }
        if (AttackingActor != nullptr && AttackingActor != DamagedActor) {
            if (ICombatControllerInterface* CombatController = Cast<ICombatControllerInterface>(DamagedController)) {
                CombatController->SetLastDmgCauser(AttackingActor);
            }
        }

        // Clamp health
        Health = FMath::Clamp(Health, 0.0f, MaxHealth);
        if (Health <= 0) {
            DamagedActor->SetLifeSpan(0.001f);
        }
    }
}

FGameplayAttribute UMyAttributeSet::MaxHealthAttribute() {
    static UProperty* Property = FindFieldChecked<UProperty>(UMyAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMyAttributeSet, MaxHealth));
    return FGameplayAttribute(Property);
}

FGameplayAttribute UMyAttributeSet::BaseAttackPowerAttribute() {
    static UProperty* Property = FindFieldChecked<UProperty>(UMyAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMyAttributeSet, BaseAttackPower));
    return FGameplayAttribute(Property);
}

FGameplayAttribute UMyAttributeSet::BaseHealingPowerAttribute() {
    static UProperty* Property = FindFieldChecked<UProperty>(UMyAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMyAttributeSet, BaseHealingPower));
    return FGameplayAttribute(Property);
}

FGameplayAttribute UMyAttributeSet::HealthAttribute() {
    static UProperty* Property = FindFieldChecked<UProperty>(UMyAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMyAttributeSet, Health));
    return FGameplayAttribute(Property);
}
