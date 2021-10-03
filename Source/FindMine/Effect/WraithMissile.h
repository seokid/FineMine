// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "ParticleProjectile.h"
#include "WraithMissile.generated.h"

/**
 * 
 */
UCLASS()
class FINDMINE_API AWraithMissile : public AParticleProjectile
{
	GENERATED_BODY()

public:
	AWraithMissile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void StopEvent(const FHitResult& result) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
