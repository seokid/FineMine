// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffSkill.h"

ABuffSkill::ABuffSkill()
{
	PrimaryActorTick.bCanEverTick = true;

	m_AccTime = 0.f;
}
// Called when the game starts or when spawned
void ABuffSkill::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABuffSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector OwnerLoc = m_SkillOwner->GetActorLocation();
	OwnerLoc.Z = GetActorLocation().Z;
	SetActorLocation(OwnerLoc);

	m_AccTime += DeltaTime;

	if (m_SkillInfo.Duration <= m_AccTime)
		Destroy();

}

