// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuffSkill.h"
#include "IceWall.generated.h"

/**
 * 
 */
UCLASS()
class FINDMINE_API AIceWall : public ABuffSkill
{
	GENERATED_BODY()

public:
	AIceWall();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent*	m_Body;

	float			m_TickAccTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
