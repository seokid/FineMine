// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"


UENUM(BlueprintType)
enum class EInputState : uint8
{
	Attack,
	Move,
	Skill1,
	Skill2,
	Skill3,
	Skill4,
	SkillEnd,
	End,
};

UCLASS()
class FINDMINE_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerCharacterController();

protected:
	bool						m_bLButtonPress;
	bool						m_bRButtonPress;
	bool						m_bAttackPress;

	EInputState					m_InputState;

public:
	virtual void PlayerTick(float DeltaTime);
	virtual void SetupInputComponent();

private:
	void LootAt(AActor* Actor, FVector Location);
	void SkillSetting(int8 SkillIdx);

	void LButtonPress();
	void LButtonRelease();
	void LButtonClick();

	void RButtonPress();
	void RButtonRelease();
	void RButtonDown();
	void RButtonClick();
	

	void AttackButtonRelease();
	void Skill1ButtonRelease();
	void Skill2ButtonRelease();
	void Skill3ButtonRelease();
	void Skill4ButtonRelease();
};