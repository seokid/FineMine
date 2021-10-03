// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "../PlayerCharacter.h"
#include "../../Effect/Skill.h"
#include "../../UI/SkillRange.h"
#include "../../Effect/ParticleBlock.h"
#include "Phase.generated.h"

UCLASS()
class FINDMINE_API APhase : public APlayerCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APhase();

protected:
	TArray<UAnimMontage*>				m_AttackMontageArray;
	TArray<UAnimMontage*>				m_SkillMontageArray;

	TArray <TSubclassOf<ASkill>>		m_SkillClassArray;
	TArray<TSubclassOf<ASkillRange>>	m_SkillRangeClassArray;

	ASkillRange*						m_SkillRange;
	int8								m_AttackIndex;

protected: 
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void AttackAnim() override;
	virtual void SkillAnim(int8 SkillIdx) override;
	virtual void SkillReady(int8 SkillIdx) override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NormalAttack() override;
	virtual void Skill(int8 SkillIdx) override;
	
	virtual void AttackEnd() override;
};
