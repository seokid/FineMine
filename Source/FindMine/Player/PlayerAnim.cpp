// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "PlayerCharacter.h"

UPlayerAnim::UPlayerAnim()
{
	m_Direction = 0.f;
	m_Speed = 0.f;
	m_Attack = false;
	m_OnGround = true;
	m_SkillIdx = 0;
}


void UPlayerAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (Player)
	{
		UCharacterMovementComponent* Movement = Player->GetCharacterMovement();

		if (Movement)
		{
			m_Speed = Movement->Velocity.Size();
		}
	}

}

void UPlayerAnim::AnimNotify_NormalAttack()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());	//UObejct 형변환은 반드시 Cast를 사용해야한다
	if (Player)
		Player->NormalAttack();

}

void UPlayerAnim::AnimNotify_AttackEnd()
{
	m_Attack = false;

	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());	//UObejct 형변환은 반드시 Cast를 사용해야한다
	if (Player)
		Player->AttackEnd();
}

void UPlayerAnim::AnimNotify_Skill()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());	//UObejct 형변환은 반드시 Cast를 사용해야한다
	if (Player)
		Player->Skill(m_SkillIdx);
}