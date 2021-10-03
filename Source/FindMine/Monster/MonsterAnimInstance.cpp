// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "Monster.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
	m_OnGround = true;
	m_AnimType = EMonsterAnimType::Idle;
	m_Hit = 0.f;


}

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());	//UObejct ����ȯ�� �ݵ�� Cast�� ����ؾ��Ѵ�

	if (Monster)
	{
		UCharacterMovementComponent* Movement = Monster->GetCharacterMovement();

		if (Movement)
		{
			bool OnGround = Movement->IsMovingOnGround();
			m_OnGround = OnGround;
		}
	}
}
void UMonsterAnimInstance::AnimNotify_NormalAttack()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());	//UObejct ����ȯ�� �ݵ�� Cast�� ����ؾ��Ѵ�
	if (Monster)
		Monster->NormalAttack();
}


void UMonsterAnimInstance::AnimNotify_AttackEnd()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());	//UObejct ����ȯ�� �ݵ�� Cast�� ����ؾ��Ѵ�
	if (Monster)
		Monster->SetAttackEnd(true);
}

void UMonsterAnimInstance::AnimNotify_HitEnd()
{
	SetHit(0.f);
}


void UMonsterAnimInstance::AnimNotify_DeathEnd()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());	//UObejct ����ȯ�� �ݵ�� Cast�� ����ؾ��Ѵ�
	if (Monster)
		Monster->Death();
}