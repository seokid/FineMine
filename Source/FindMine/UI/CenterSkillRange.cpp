// Fill out your copyright notice in the Description page of Project Settings.


#include "CenterSkillRange.h"

ACenterSkillRange::ACenterSkillRange()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Center = CreateDefaultSubobject<USceneComponent>(TEXT("Center"));
	SetRootComponent(m_Center);
	m_Decal->SetupAttachment(m_Center);
}

// Called when the game starts or when spawned
void ACenterSkillRange::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACenterSkillRange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult result;
	bool Hit = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel8, false, result);	//복합충돌 여부 = false

	if (Hit)
	{
		APawn*	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
		SetActorLocation(Player->GetActorLocation());

		result.ImpactPoint -= Player->GetActorLocation();
		SetActorRotation(FRotator(0.f, result.ImpactPoint.Rotation().Yaw, 0.f));
	}
}

