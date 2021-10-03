// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameINfo.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

UENUM(BlueprintType)	//BP로 사용할수있는타입
enum class EMonsterAnimType : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Death,
	Skill,

};

UENUM(BlueprintType)	//BP로 사용할수있는타입
enum class EMonsterAttackType : uint8
{
	Attack1,
	Attack2,
	Attack3,
	Attack4,

};

UCLASS()
class FINDMINE_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMonsterAnimInstance();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	m_OnGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EMonsterAnimType			m_AnimType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EMonsterAttackType			m_AttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float						m_Hit;

public:
	EMonsterAnimType GetAnimType() const { return m_AnimType; }
	void ChangeAnimType(EMonsterAnimType Type) { m_AnimType = Type; }

	void SetHit(float Hit) { m_Hit = Hit; }


public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	UFUNCTION()
	void AnimNotify_NormalAttack();

	UFUNCTION()
	void AnimNotify_AttackEnd();
	
	UFUNCTION()
	void AnimNotify_HitEnd();

	UFUNCTION()
	void AnimNotify_DeathEnd();
};
