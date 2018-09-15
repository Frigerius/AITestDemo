// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "MyAttributeSet.h"

#include "AIDemoGameCharacter.generated.h"

UCLASS(Blueprintable)
class AAIDemoGameCharacter : public ACharacter, public IAbilitySystemInterface {
    GENERATED_BODY()

public:
    AAIDemoGameCharacter();

    // Called every frame.
    virtual void Tick(float DeltaSeconds) override;

    /** Returns TopDownCameraComponent subobject **/
    FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
    /** Returns CameraBoom subobject **/
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    /** Returns CursorToWorld subobject **/
    FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    float BaseTurnRate;

    /** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    float BaseLookUpRate;

    UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; };

    UPROPERTY(EditAnywhere)
    class UMyAbilitySet* AbilitySet;

    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere)
    UMyAttributeSet* AttributeSet;

private:
    /** Top down camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* TopDownCameraComponent;

    /** Camera boom positioning the camera above the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;

    /** A decal that projects to the cursor location. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UDecalComponent* CursorToWorld;

    /** Our ability system */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
    class UAbilitySystemComponent* AbilitySystem;

protected:
    /**
     * Called via input to turn at a given rate.
     * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
     */
    void TurnAtRate(float Rate);

    /**
     * Called via input to turn look up/down at a given rate.
     * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
     */
    void LookUpAtRate(float Rate);

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
