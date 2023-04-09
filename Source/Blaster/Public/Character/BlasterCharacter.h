// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BlasterCharacter.generated.h"

UCLASS()
class BLASTER_API ABlasterCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ABlasterCharacter();

#pragma region Actor Interface
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void PostInitializeComponents() override;
#pragma endregion  Actor Interface

#pragma region Setter/Getter
    void SetOverlappingWeapon(AWeapon* InWeapon);
    bool IsWeaponEquipped();
    bool IsAiming();
#pragma endregion  Setter/Getter

protected:
    virtual void BeginPlay() override;

    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void EquipButtonPressed();
    void CrouchButtonPressed();
    void AimButtonPressed();
    void AimButtonReleased();

private:
    UPROPERTY(EditAnywhere, Category = Camera)
    class USpringArmComponent* CameraBoom;

    UPROPERTY(EditAnywhere, Category = Camera)
    class UCameraComponent* FollowCamera;

    UPROPERTY(ReplicatedUsing=OnRep_OverlappingWeapon)
    class AWeapon* OverlappingWeapon;

    UPROPERTY(VisibleAnywhere)
    class UCombatComponent* CombatComponent;

    UFUNCTION(Server, Reliable)
    void ServerEquipButtonPressed();

#pragma region RepNotifyRegion
    UFUNCTION()
    void OnRep_OverlappingWeapon(AWeapon* InLastWeapon);
#pragma endregion RepNotifyRegion

};
