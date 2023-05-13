// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/BlasterAnimInstance.h"
#include "BlasterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapon/Weapon.h"

void UBlasterAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
}

void UBlasterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (BlasterCharacter == nullptr)
    {
        BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
    }

    if (BlasterCharacter == nullptr) return;

    Speed = BlasterCharacter->GetSpeed();

    // Update animation flags
    bIsInAir = BlasterCharacter->GetCharacterMovement()->IsFalling();
    bIsAccelerating = BlasterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.0f;
    bWeaponEquipped = BlasterCharacter->IsWeaponEquipped();
    EquippedWeapon = BlasterCharacter->GetEquippedWeapon();
    bIsCrouched = BlasterCharacter->bIsCrouched;
    bIsAiming = BlasterCharacter->IsAiming();

    // Calculate YawOffset
    {
        const FRotator AimRotation = BlasterCharacter->GetBaseAimRotation();
        const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(BlasterCharacter->GetVelocity()); 
        FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
        DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaSeconds, 5.f);
        YawOffset = DeltaRotation.Yaw;
    }

    // Calculate Lean
    {
        CharacterRotationLastFrame = CharacterRotation;
        CharacterRotation = BlasterCharacter->GetActorRotation();
        const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
        const float Target = Delta.Yaw / DeltaSeconds;
        const float Interp = FMath::FInterpTo(Lean, Target, DeltaSeconds, 6.0);
        Lean = FMath::Clamp(Interp, -90.f, 90.f);
    }

    AO_Yaw = BlasterCharacter->GetAO_Yaw();
    AO_Pitch = BlasterCharacter->GetAO_Pitch();

    SetLeftHand();
}

void UBlasterAnimInstance::SetLeftHand()
{
    if (bWeaponEquipped && EquippedWeapon != nullptr)
    {
        const USkeletalMeshComponent* WeaponMesh = EquippedWeapon->GetWeaponMesh();
        const USkeletalMeshComponent* CharacterMesh = BlasterCharacter->GetMesh();
        if (WeaponMesh != nullptr && CharacterMesh != nullptr)
        {
            LeftHandTransform = WeaponMesh->GetSocketTransform(FName("LeftHandSocket"), RTS_World);
            
            FVector OutPosition;
            FRotator OutRotation;
            CharacterMesh->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator,OutPosition , OutRotation);
            LeftHandTransform.SetLocation(OutPosition);
            LeftHandTransform.SetRotation(FQuat(OutRotation));
        }
    }
}
