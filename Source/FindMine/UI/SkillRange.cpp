// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillRange.h"

// Sets default values
ASkillRange::ASkillRange()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	SetRootComponent(m_Decal);
}

// Called when the game starts or when spawned
void ASkillRange::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkillRange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

