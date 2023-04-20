// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterComponents/CombatComponent.h"

#include "BlasterCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Weapon/Weapon.h"

UCombatComponent::UCombatComponent()
    : BaseWalkSpeed(600.f)
    , AimWalkSpeed(450.f)
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UCombatComponent, EquippedWeapon);
    DOREPLIFETIME(UCombatComponent, bAiming);
}

void UCombatComponent::BeginPlay()
{
    Super::BeginPlay();

    SetMaxWalkSpeed(BaseWalkSpeed);
}

void UCombatComponent::SetAiming(bool bIsAiming)
{
    bAiming = bIsAiming;
    bAiming ? SetMaxWalkSpeed(AimWalkSpeed) : SetMaxWalkSpeed(BaseWalkSpeed);
    ServerSetAiming(bAiming);
}

void UCombatComponent::ServerSetAiming_Implementation(const bool bIsAiming)
{
    bAiming = bIsAiming;
    bAiming ? SetMaxWalkSpeed(AimWalkSpeed) : SetMaxWalkSpeed(BaseWalkSpeed);
}

void UCombatComponent::OnRep_EquippedWeapon()
{
    if (EquippedWeapon != nullptr && Character != nullptr)
    {
        Character->GetCharacterMovement()->bOrientRotationToMovement = false;
        Character->bUseControllerRotationYaw = true;
    }
}

void UCombatComponent::EquipWeapon(AWeapon* InWeaponToEquip)
{
    if (Character == nullptr || InWeaponToEquip == nullptr) return;

    EquippedWeapon = InWeaponToEquip;
    EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);
    const USkeletalMeshSocket* HandSocket = Character->GetMesh()->GetSocketByName(FName("RightHandSocket"));

    if (HandSocket != nullptr)
    {
        HandSocket->AttachActor(EquippedWeapon, Character->GetMesh());
    }

    EquippedWeapon->SetOwner(Character);
    Character->GetCharacterMovement()->bOrientRotationToMovement = false;
    Character->bUseControllerRotationYaw = true;
}

void UCombatComponent::SetMaxWalkSpeed(const float InMaxWalkSpeed) const
{
    if (Character != nullptr)
    {
        if (UCharacterMovementComponent* CharacterMovement = Character->GetCharacterMovement())
        {
            CharacterMovement->MaxWalkSpeed = InMaxWalkSpeed;
        }
    }
}
