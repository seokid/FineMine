// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Skill.h"
#include "BuffSkill.generated.h"

/**
 * 
 */
UCLASS()
class FINDMINE_API ABuffSkill : public ASkill
{
	GENERATED_BODY()
public:
	ABuffSkill();

protected:
	float	m_AccTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
