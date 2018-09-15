// Fill out your copyright notice in the Description page of Project Settings.

#include "FireballProjectile.h"
#include "UnrealNetwork.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFireballProjectile::AFireballProjectile() {
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionBlockComp0"));
    CollisionComponent->InitSphereRadius(0.0f);
    CollisionComponent->bAbsoluteScale = true;
    CollisionComponent->SetCanEverAffectNavigation(false);
    // CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
    RootComponent = CollisionComponent;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp0"));
    MeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetCanEverAffectNavigation(false);
    MeshComponent->CastShadow = false;
    MeshComponent->SetGenerateOverlapEvents(false);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp0"));
    MovementComponent->UpdatedComponent = RootComponent;

    bReplicates = true;
    bHasTarget = false;
}

// Called when the game starts or when spawned
void AFireballProjectile::BeginPlay() {
    Super::BeginPlay();

    if (Role == ROLE_Authority) {
        if (Instigator) {
            FTransform trans = Instigator->GetActorTransform();
            // trans.AddToTranslation(FVector(0, 0, 100));
            SetActorTransform(trans, false);
        }

        SpawnOrigin = GetActorLocation();
        if (bHasTarget) {
            SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnOrigin, TargetPosition).GetNormalized();
            SetActorRotation(SpawnRotation);
        } else {
            SpawnRotation = GetActorRotation().GetNormalized();
        }
    }

    const FVector Direction = SpawnRotation.Vector();
    const float Speed = GetLaunchSpeed();

    Launch(Direction, Speed);
    SetLifeSpan(1);
}

void AFireballProjectile::Launch(const FVector& Dir, float Speed) {
    FVector const DirNorm = Dir.GetSafeNormal();

    MovementComponent->Velocity = Speed * DirNorm;
}

void AFireballProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION(AFireballProjectile, SpawnOrigin, COND_InitialOnly);
    DOREPLIFETIME_CONDITION(AFireballProjectile, SpawnRotation, COND_InitialOnly);
    DOREPLIFETIME_CONDITION(AFireballProjectile, LaunchSpeed, COND_InitialOnly);
}

float AFireballProjectile::GetLaunchSpeed() const {
    return LaunchSpeed;
}
