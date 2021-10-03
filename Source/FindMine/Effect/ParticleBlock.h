// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "ParticleBlock.generated.h"

UCLASS()
class FINDMINE_API AParticleBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParticleBlock();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent*					m_Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent*		m_Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float							m_Duration;


	APawn*							m_ParticleOwner;

public:
	void SeParticletOwner(APawn* ParticleOwner) { m_ParticleOwner = ParticleOwner;}
	void SetDuration(float Duration) { m_Duration = Duration; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ParticleEnd() {}

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
