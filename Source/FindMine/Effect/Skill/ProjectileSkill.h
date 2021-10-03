// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Skill.h"
#include "ProjectileSkill.generated.h"

/**
 * 
 */
UCLASS()
class FINDMINE_API AProjectileSkill : public ASkill
{
	GENERATED_BODY()
public:
	AProjectileSkill();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent*					m_Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent*	m_Movement;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void StopEvent(const FHitResult& result);
public:
	UFUNCTION()
	void PorjectileStop(const FHitResult& result);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
