// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SkillRange.h"
#include "CenterSkillRange.generated.h"

/**
 * 
 */
UCLASS()
class FINDMINE_API ACenterSkillRange : public ASkillRange
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACenterSkillRange();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USceneComponent*	m_Center;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
