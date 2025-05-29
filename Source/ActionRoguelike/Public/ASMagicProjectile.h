// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API AASMagicProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AASMagicProjectile();

protected:

	//collision component
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	//component that goes on a straight line with a velocity
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	//particle system
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;

	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
