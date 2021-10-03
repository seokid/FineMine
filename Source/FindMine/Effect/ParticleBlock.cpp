// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticleBlock.h"

// Sets default values
AParticleBlock::AParticleBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Body = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	m_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	SetRootComponent(m_Body);
	m_Particle->SetupAttachment(m_Body);

	m_Duration = 1.f;
}

// Called when the game starts or when spawned
void AParticleBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParticleBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_Duration -= DeltaTime;

	if (0.f > m_Duration)
	{
		ParticleEnd();
		Destroy();
	}
		
}

