// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "ProjectileSkill.h"
#include "FireBall.generated.h"

/**
 * 
 */
UCLASS()
class FINDMINE_API AFireBall : public AProjectileSkill
{
	GENERATED_BODY()

public:
	AFireBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void StopEvent(const FHitResult& result) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
