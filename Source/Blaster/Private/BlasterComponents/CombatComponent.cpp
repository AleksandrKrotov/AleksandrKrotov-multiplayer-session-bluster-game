// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterComponents/CombatComponent.h"

#include "BlasterCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Weapon/Weapon.h"

UCombatComponent::UCombatComponent()
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
}

void UCombatComponent::SetAiming(bool bIsAiming)
{
    bAiming = bIsAiming;
    
    ServerSetAiming(bIsAiming);
}

void UCombatComponent::OnRep_EquippedWeapon()
{
    if (EquippedWeapon != nullptr && Character != nullptr)
    {
        Character->GetCharacterMovement()->bOrientRotationToMovement = false;
        Character->bUseControllerRotationYaw = true;
    }
}

void UCombatComponent::ServerSetAiming_Implementation(bool bIsAiming)
{
    bAiming = bIsAiming;
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
