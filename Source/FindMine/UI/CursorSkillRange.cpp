// Fill out your copyright notice in the Description page of Project Settings.


#include "CursorSkillRange.h"

ACursorSkillRange::ACursorSkillRange()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACursorSkillRange::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACursorSkillRange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult result;
	bool Hit = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel8, false, result);	//복합충돌 여부 = false

	if (Hit)
	{
		SetActorLocation(result.ImpactPoint);
	}
}

