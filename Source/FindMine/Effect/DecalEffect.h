// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "DecalEffect.generated.h"

UCLASS()
class FINDMINE_API ADecalEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADecalEffect();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UDecalComponent*	m_Decal;


public:

	void SetDecalSize(const FVector& DecalSize) { m_Decal->DecalSize = DecalSize; }
	void SetDecalMaterial(UMaterial* DecalMaterial) { m_Decal->SetDecalMaterial(DecalMaterial); }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
