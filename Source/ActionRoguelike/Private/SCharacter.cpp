// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionRoguelike/Public/SCharacter.h"
#include "DrawDebugHelpers.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
    SpringArmComp->SetupAttachment(RootComponent);
    SpringArmComp->bUsePawnControlRotation = true;

    CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
    CameraComp->SetupAttachment(SpringArmComp);

    GetCharacterMovement()->bOrientRotationToMovement = true;
    bUseControllerRotationYaw = false;
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
    
    PlayerInputComponent->BindAxis("Turn", this, &ASCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::AddControllerPitchInput);

    PlayerInputComponent->BindAction("PrimaryAttack",IE_Pressed,this, &ASCharacter::PrimaryAttack);
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ASCharacter::MoveForward(float value)
{
    FRotator ControlRot = GetControlRotation();
    ControlRot.Pitch = 0.0f;
    ControlRot.Roll = 0.0f;

    // x forward (red)
    // y is right (green)
    // z is up (blue)
    
    AddMovementInput(ControlRot.Vector(), value);
}

void ASCharacter::MoveRight(float value)
{
    FRotator ControlRot = GetControlRotation();
    ControlRot.Pitch = 0.0f;
    ControlRot.Roll = 0.0f;

    FVector RightVector = FRotationMatrix(ControlRot).GetUnitAxis(EAxis::Y);
    
    AddMovementInput(RightVector, value);
}

void ASCharacter::PrimaryAttack()
{
    FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
    
    FTransform SpawnTM = FTransform(GetControlRotation(),HandLocation);
    
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    
    GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTM,SpawnParams);
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // -- Rotation Visualization -- //
    const float DrawScale = 100.0f;
    const float Thickness = 5.0f;

    FVector LineStart = GetActorLocation();
    // Offset to the right of pawn
    LineStart += GetActorRightVector() * 100.0f;
    // Set line end in direction of the actor's forward
    FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
    // Draw Actor's Direction
    DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

    FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
    // Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
    DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
}