// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AIDemoGamePlayerController.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "AIDemoGameCharacter.h"
#include "EnemyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AAIDemoGamePlayerController::AAIDemoGamePlayerController() {
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Crosshairs;
    Target = nullptr;
    bAutoAttack = false;
    LastDmgCauser = nullptr;
}

FString AAIDemoGamePlayerController::GetTargetName() const {
    if (Target) {
        return Target->GetName();
    }
    return FString();
}

AActor* AAIDemoGamePlayerController::GetTarget() const {
    return Target;
}

AActor* AAIDemoGamePlayerController::GetLastDmgCauser() const {
    return LastDmgCauser;
}

void AAIDemoGamePlayerController::SetLastDmgCauser(AActor* DmgCauser) {
    if (DmgCauser != nullptr)
        LastDmgCauser = DmgCauser;
}

void AAIDemoGamePlayerController::PlayerTick(float DeltaTime) {
    Super::PlayerTick(DeltaTime);

    // keep updating the destination every tick while desired
    if (bMoveToMouseCursor) {
        MoveToMouseCursor();
    }
    if (Target) {
        if (AAIDemoGameCharacter* MyPawn = Cast<AAIDemoGameCharacter>(GetPawn())) {
            if (bAutoAttack && MyPawn->GetCursorToWorld()) {
                MyPawn->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(MyPawn->GetActorLocation(), Target->GetActorLocation()));
                MyPawn->GetAbilitySystemComponent()->AbilityLocalInputPressed(0);
            }
            /*float const dist = FVector::Dist(Target->GetActorLocation(), MyPawn->GetActorLocation());
            if (GEngine) {
                GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Black, FString::Printf(TEXT("%f"), dist));
            }*/
        }
    }
}

void AAIDemoGamePlayerController::SetupInputComponent() {
    // set up gameplay key bindings
    Super::SetupInputComponent();

    // InputComponent->BindAction("LMBClick", IE_Pressed, this, &AAIDemoGamePlayerController::OnSetDestinationPressed);
    InputComponent->BindAction("LMBClick", IE_Released, this, &AAIDemoGamePlayerController::MoveToMouseCursor);
    InputComponent->BindAction("LMBClick", IE_DoubleClick, this, &AAIDemoGamePlayerController::AttackEnemy);
}

void AAIDemoGamePlayerController::MoveToMouseCursor() {
    // Trace to see what is under the mouse cursor
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_Visibility, false, Hit);

    if (Hit.bBlockingHit) {
        if (AEnemyCharacter* enemy = Cast<AEnemyCharacter>(Hit.Actor.Get())) {
            Target = enemy;
            bAutoAttack = false;
            APawn* const MyPawn = GetPawn();
            if (MyPawn) {
                MyPawn->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(MyPawn->GetActorLocation(), Target->GetActorLocation()));
            }
        } else {
            // We hit something, move there
            SetNewMoveDestination(Hit.ImpactPoint);
        }
    }
}

void AAIDemoGamePlayerController::SetNewMoveDestination(const FVector DestLocation) {
    APawn* const MyPawn = GetPawn();
    if (MyPawn) {
        float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

        // We need to issue move command only if far enough in order for walk animation to play correctly
        if (Distance > 120.0f) {
            UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
        }
    }
}

void AAIDemoGamePlayerController::OnSetDestinationPressed() {
    // set flag to keep updating destination until released
    bMoveToMouseCursor = true;
}

void AAIDemoGamePlayerController::OnSetDestinationReleased() {
    // clear flag to indicate we should stop updating the destination
    bMoveToMouseCursor = false;
}

void AAIDemoGamePlayerController::AttackEnemy() {
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_Visibility, false, Hit);

    if (Hit.bBlockingHit) {
        if (AEnemyCharacter* enemy = Cast<AEnemyCharacter>(Hit.Actor.Get())) {
            Target = enemy;
            bAutoAttack = true;
            if (APawn* const MyPawn = GetPawn()) {
                float const dist = FVector::DistSquared(enemy->GetActorLocation(), MyPawn->GetActorLocation());
                static const float minDist = 300 * 300;
                if (dist > minDist) {
                    FVector dir = FVector(enemy->GetActorLocation() - MyPawn->GetActorLocation());
                    dir.Normalize();
                    SetNewMoveDestination(dir * dist - minDist);
                }
            }
        } else {
            Target = nullptr;
            bAutoAttack = false;
        }
    }
}

void AAIDemoGamePlayerController::SetTarget(AEnemyCharacter* NewTarget) {
    if (NewTarget != nullptr) {
        Target = NewTarget;
        Target->OnDestroyed.AddDynamic(this, &AAIDemoGamePlayerController::OnTargetDied);
    } else {
        Target = nullptr;
    }
}

void AAIDemoGamePlayerController::OnTargetDied(AActor* Actor) {
    if (Target == Actor) {
        Target = nullptr;
    }
}
