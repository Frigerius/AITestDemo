// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MyAbilitySet.h"
#include "GameplayAbilityTypes.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter() {
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true;  // Rotate character to moving direction
    GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;

    // Activate ticking in order to update the cursor every frame.
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;

    // Our ability system component.
    AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
    AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay() {
    Super::BeginPlay();
    if (AbilitySystem) {
        if (HasAuthority() && AbilitySet != nullptr) {
            AbilitySet->GiveAbilities(AbilitySystem);
        }
        AbilitySystem->InitAbilityActorInfo(this, this);
    }
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    AbilitySystem->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbilityInputBinds("ConfirmInput", "CancelInput", "Spells"));
}
