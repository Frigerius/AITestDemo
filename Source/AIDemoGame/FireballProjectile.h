// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GASTypes.h"
#include "FireballProjectile.generated.h"

UCLASS()
class AIDEMOGAME_API AFireballProjectile : public AActor {
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AFireballProjectile();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    void Launch(const FVector& Dir, float Speed);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    float GetLaunchSpeed() const;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (ExposeOnSpawn = true))
    FGASEffectApplicationContainer OnHitEffectsContainer;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
    class USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* MeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
    class UProjectileMovementComponent* MovementComponent;

    UPROPERTY(Replicated)
    FVector SpawnOrigin;

    UPROPERTY(Replicated)
    FRotator SpawnRotation;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
    float LaunchSpeed;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
    FVector TargetPosition;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
    bool bHasTarget;
};
