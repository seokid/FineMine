// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "SkillRange.h"
#include "CursorSkillRange.generated.h"

/**
 * 
 */
UCLASS()
class FINDMINE_API ACursorSkillRange : public ASkillRange
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACursorSkillRange();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
