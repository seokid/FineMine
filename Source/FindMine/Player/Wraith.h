// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "PlayerCharacter.h"
#include "../Effect/WraithMissile.h"
#include "Wraith.generated.h"

/**
 * 
 */
UCLASS()
class FINDMINE_API AWraith : public APlayerCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWraith();

protected:
	TArray<UAnimMontage*>				m_AttackMontageArray;
	TArray<UAnimMontage*>				m_SkillMontageArray;

	TSubclassOf<AWraithMissile>			m_MissileClass;

	int32								m_AttackIndex;
	int32								m_SkillIndex;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void AttackAnim() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void NormalAttack() override;
	virtual void AttackEnd() override;
};
