// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticleProjectile.h"

// Sets default values
AParticleProjectile::AParticleProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	m_Body = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));

	m_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	m_Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	SetRootComponent(m_Body);
	m_Particle->SetupAttachment(m_Body);

	m_Movement->SetUpdatedComponent(m_Body);
	m_Movement->InitialSpeed = 1000.f;
	m_Movement->ProjectileGravityScale = 0.f;

	m_Distance = 2000.f;

	m_PlayerOwner = nullptr;
	m_MonsterOwner = nullptr;

}

// Called when the game starts or when spawned
void AParticleProjectile::BeginPlay()
{
	Super::BeginPlay();

	m_Movement->OnProjectileStop.AddDynamic(this, &AParticleProjectile::PorjectileStop);

	
}

// Called every frame
void AParticleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_Distance -= m_Movement->Velocity.Size() * DeltaTime;

	if (m_Distance <= 0.f)
		Destroy();
}

void AParticleProjectile::PorjectileStop(const FHitResult& result)
{
	StopEvent(result);
}

void AParticleProjectile::StopEvent(const FHitResult& result)
{
}