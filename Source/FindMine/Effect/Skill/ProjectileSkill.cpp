// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSkill.h"

AProjectileSkill::AProjectileSkill()
{
	m_Body = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	m_Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	SetRootComponent(m_Body);
	m_Particle->SetupAttachment(m_Body);

	m_Movement->SetUpdatedComponent(m_Body);
	m_Movement->InitialSpeed = 1000.f;
	m_Movement->ProjectileGravityScale = 0.f;
}


// Called when the game starts or when spawned
void AProjectileSkill::BeginPlay()
{
	Super::BeginPlay();

	m_Movement->OnProjectileStop.AddDynamic(this, &AProjectileSkill::PorjectileStop);
}

// Called every frame
void AProjectileSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_SkillInfo.Distance -= m_Movement->Velocity.Size() * DeltaTime;

	if (m_SkillInfo.Distance <= 0.f)
		Destroy();
}

void AProjectileSkill::PorjectileStop(const FHitResult& result)
{
	StopEvent(result);
}

void AProjectileSkill::StopEvent(const FHitResult& result)
{
}