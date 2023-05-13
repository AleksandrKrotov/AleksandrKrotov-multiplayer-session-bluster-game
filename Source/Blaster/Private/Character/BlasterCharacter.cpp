// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/BlasterCharacter.h"

#include "BlasterComponents/CombatComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Weapon/Weapon.h"

ABlasterCharacter::ABlasterCharacter()
    : StartingAimRotation(FRotator::ZeroRotator)
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoomComponent"));
    CameraBoom->SetupAttachment(GetMesh());
    CameraBoom->TargetArmLength = 600.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCameraComponent"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    bUseControllerRotationYaw = false;
    if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
    {
        MovementComponent->bOrientRotationToMovement = true;
        MovementComponent->NavAgentProps.bCanCrouch = true;
    }

    CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
    CombatComponent->SetIsReplicated(true);

    if (UCapsuleComponent* Capsule = GetCapsuleComponent())
    {
        Capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    }
}

void ABlasterCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION(ABlasterCharacter, OverlappingWeapon, COND_OwnerOnly);
}

void ABlasterCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ABlasterCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AimOffset(DeltaTime);
}

void ABlasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

    PlayerInputComponent->BindAxis("MoveForward", this, &ABlasterCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ABlasterCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &ABlasterCharacter::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &ABlasterCharacter::LookUp);

    PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &ABlasterCharacter::EquipButtonPressed);
    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ABlasterCharacter::CrouchButtonPressed);

    PlayerInputComponent->BindAction("Aim",IE_Pressed, this, &ABlasterCharacter::AimButtonPressed);
    PlayerInputComponent->BindAction("Aim",IE_Released, this, &ABlasterCharacter::AimButtonReleased);
}

void ABlasterCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    if (CombatComponent != nullptr)
    {
        CombatComponent->Character = this;
    }
}

void ABlasterCharacter::MoveForward(float Value)
{
    if (Controller != nullptr && Value != 0.0f)
    {
        const FRotator YawRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
        const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
        AddMovementInput(Direction, Value);
    }
}

void ABlasterCharacter::MoveRight(float Value)
{
    if (Controller != nullptr && Value != 0.0f)
    {
        const FRotator YawRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
        const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
        AddMovementInput(Direction, Value);
    }
}

void ABlasterCharacter::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void ABlasterCharacter::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}

void ABlasterCharacter::EquipButtonPressed()
{
    ServerEquipButtonPressed();
}

void ABlasterCharacter::ServerEquipButtonPressed_Implementation()
{
    if (CombatComponent != nullptr)
    {
        CombatComponent->EquipWeapon(OverlappingWeapon);
    }
}

void ABlasterCharacter::CrouchButtonPressed()
{
    bIsCrouched ? UnCrouch() : Crouch();
}

void ABlasterCharacter::AimButtonPressed()
{
    if (CombatComponent != nullptr)
    {
        CombatComponent->SetAiming(true);
    }
}

void ABlasterCharacter::AimButtonReleased()
{
    if (CombatComponent != nullptr)
    {
        CombatComponent->SetAiming(false);
    }
}

void ABlasterCharacter::AimOffset(float DeltaTime)
{
    if (CombatComponent != nullptr && CombatComponent->EquippedWeapon == nullptr)
    {
        StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
        return;
    }

    const float Speed = GetSpeed();
    const bool bIsInAir = GetCharacterMovement()->IsFalling();

    if (Speed == 0.f &&  !bIsInAir)
    {
        const FRotator CurrentAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
        const FRotator DeltaAimRotation = UKismetMathLibrary::NormalizedDeltaRotator(CurrentAimRotation, StartingAimRotation);
        AO_Yaw = DeltaAimRotation.Yaw;
        bUseControllerRotationYaw = false;
    }

    if (Speed > 0.f || bIsInAir)
    {
        StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
        AO_Yaw = 0.f;
        bUseControllerRotationYaw = true;
    }

    AO_Pitch = GetBaseAimRotation().Pitch;
    if (!IsLocallyControlled() && AO_Pitch > 180.0f)
    {t
        // Convert from range [0, 360] to [-180, 180]
        AO_Pitch = AO_Pitch - 360;
    }
}

void ABlasterCharacter::SetOverlappingWeapon(AWeapon* InWeapon)
{
    AWeapon* LastWeapon = OverlappingWeapon;
    OverlappingWeapon = InWeapon;

    if (IsLocallyControlled())
    {
        OnRep_OverlappingWeapon(LastWeapon);
    }
}

bool ABlasterCharacter::IsWeaponEquipped() const
{
    return (CombatComponent != nullptr && CombatComponent->EquippedWeapon != nullptr);
}

bool ABlasterCharacter::IsAiming() const
{
    return (CombatComponent != nullptr && CombatComponent->bAiming); 
}

float ABlasterCharacter::GetSpeed() const
{
    FVector Velocity = GetVelocity();
    Velocity.Z = 0.0f;
    return  Velocity.Size();
}

void ABlasterCharacter::OnRep_OverlappingWeapon(AWeapon* InLastWeapon)
{
    if (OverlappingWeapon != nullptr)
    {
        OverlappingWeapon->ShowPickupWidget(true);
    }
    else if (InLastWeapon != nullptr)
    {
        InLastWeapon->ShowPickupWidget(false);
    }
}
