// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "ParticleProjectile.generated.h"

UCLASS()
class FINDMINE_API AParticleProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParticleProjectile();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent*					m_Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent*		m_Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent*	m_Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float							m_Distance;

	class APlayerCharacter*			m_PlayerOwner;
	class AMonster*					m_MonsterOwner;

public:
	void SetDistance(float Distance) { m_Distance = Distance; }
	void SetPlayerOwner(APlayerCharacter* PlayerOwner) { m_PlayerOwner = PlayerOwner; }
	void SetMonsterOwner(AMonster* MonsterOwner) { m_MonsterOwner = MonsterOwner; }

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
