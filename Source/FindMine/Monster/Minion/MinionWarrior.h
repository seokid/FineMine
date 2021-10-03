// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Minion.h"
#include "MinionWarrior.generated.h"

/**
 * 
 */
UCLASS()
class FINDMINE_API AMinionWarrior : public AMinion
{
	GENERATED_BODY()
	
public:
	AMinionWarrior();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NormalAttack() override;
};
