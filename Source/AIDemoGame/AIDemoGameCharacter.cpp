// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AIDemoGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "AIDemoGamePlayerController.h"
#include "MyAbilitySet.h"
#include "GameplayAbilityTypes.h"

AAIDemoGameCharacter::AAIDemoGameCharacter() {
    // Set size for player capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Don't rotate character to camera direction
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true;  // Rotate character to moving direction
    GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;

    // Create a camera boom...
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->bAbsoluteRotation = true;  // Don't want arm to rotate when character does
    CameraBoom->TargetArmLength = 800.f;
    CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
    CameraBoom->bDoCollisionTest = false;  // Don't want to pull camera in when it collides with level
    CameraBoom->bUsePawnControlRotation = true;

    // Create a camera...
    TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
    TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    TopDownCameraComponent->bUsePawnControlRotation = false;  // Camera does not rotate relative to arm

    // Create a decal in the world to show the cursor's location
    CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
    CursorToWorld->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
    if (DecalMaterialAsset.Succeeded()) {
        CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
    }
    CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
    CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

    // Activate ticking in order to update the cursor every frame.
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;

    // set our turn rates for input
    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;

    // Our ability system component.
    AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
    AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));
}

void AAIDemoGameCharacter::Tick(float DeltaSeconds) {
    Super::Tick(DeltaSeconds);

    if (CursorToWorld != nullptr) {
        if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled()) {
            if (UWorld* World = GetWorld()) {
                FHitResult HitResult;
                FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
                FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
                FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
                Params.AddIgnoredActor(this);
                World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
                FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
                CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
            }
        } else if (APlayerController* PC = Cast<APlayerController>(GetController())) {
            FHitResult TraceHitResult;
            PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
            FVector CursorFV = TraceHitResult.ImpactNormal;
            FRotator CursorR = CursorFV.Rotation();
            CursorToWorld->SetWorldLocation(TraceHitResult.Location);
            CursorToWorld->SetWorldRotation(CursorR);
        }
    }
}

void AAIDemoGameCharacter::BeginPlay() {
    Super::BeginPlay();
    if (AbilitySystem) {
        // FGameplayAbilityActorInfo* actorInfo = new FGameplayAbilityActorInfo();
        // actorInfo->InitFromActor(this, this, AbilitySystem);
        // AbilitySystem->AbilityActorInfo = TSharedPtr<FGameplayAbilityActorInfo>(actorInfo);
        if (HasAuthority() && AbilitySet != nullptr) {
            AbilitySet->GiveAbilities(AbilitySystem);
        }
        AbilitySystem->InitAbilityActorInfo(this, this);
    }
}

void AAIDemoGameCharacter::TurnAtRate(float Rate) {
    // calculate delta for this frame from the rate information
    AAIDemoGamePlayerController* controller = Cast<AAIDemoGamePlayerController>(GetController());
    if (controller != nullptr) {
        if (controller->IsInputKeyDown(EKeys::RightMouseButton)) {
            AddControllerYawInput(Rate);
        }
    }
}

void AAIDemoGameCharacter::LookUpAtRate(float Rate) {
    // calculate delta for this frame from the rate information
    AAIDemoGamePlayerController* controller = Cast<AAIDemoGamePlayerController>(GetController());
    if (controller != nullptr) {
        if (controller->IsInputKeyDown(EKeys::RightMouseButton)) {
            AddControllerPitchInput(Rate);
        }
    }
}

void AAIDemoGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
    // We have 2 versions of the rotation bindings to handle different kinds of devices differently
    // "turn" handles devices that provide an absolute delta, such as a mouse.
    // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
    PlayerInputComponent->BindAxis("Turn", this, &AAIDemoGameCharacter::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUp", this, &AAIDemoGameCharacter::LookUpAtRate);
    AbilitySystem->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbilityInputBinds("ConfirmInput", "CancelInput", "EMyInputBinds"));
}
