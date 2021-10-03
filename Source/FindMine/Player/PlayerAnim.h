// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class FINDMINE_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnim();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	m_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	m_OnGround;

	int8	m_SkillIdx;

public:
	void SetDirection(float Direction) { m_Direction = Direction; }
	void SetAttack(bool Attack) { m_Attack = Attack; }
	void SetSkillIdx(int8 Idx) {m_SkillIdx = Idx;}

	bool IsAttack() const { return m_Attack; }

	
public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	UFUNCTION()							//멤버함수에 붙임
	void AnimNotify_AttackEnd();		//AnimNotify_ + Notify 명 으로 작성한다 무조건

	UFUNCTION()
	void AnimNotify_NormalAttack();
	
	UFUNCTION()
	void AnimNotify_Skill();

};
