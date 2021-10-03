// Fill out your copyright notice in the Description page of Project Settings.


#include "Phase.h"
#include "../PlayerCharacterController.h"
//#include "../../Effect/Skill/SkillRange.h"

APhase::APhase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkelAsset(TEXT("SkeletalMesh'/Game/ParagonPhase/Characters/Heroes/Phase/Meshes/Phase_GDC.Phase_GDC'"));

	if (SkelAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkelAsset.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Player/Phase/ABP_Phase.ABP_Phase_C'"));

	if (AnimAsset.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Skill1Asset(TEXT("AnimMontage'/Game/Player/Phase/AM_PhaseSkill1.AM_PhaseSkill1'"));

	if (Skill1Asset.Succeeded())
	{
		m_SkillMontageArray.Add(Skill1Asset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Skill2Asset(TEXT("AnimMontage'/Game/Player/Phase/AM_PhaseAttack1.AM_PhaseAttack1'"));

	if (Skill2Asset.Succeeded())
	{
		m_SkillMontageArray.Add(Skill2Asset.Object);
	}

	static ConstructorHelpers::FClassFinder<ASkill> IceWallAsset(TEXT("Blueprint'/Game/Effect/Skill/BP_IceWall.BP_IceWall_C'"));
	if (IceWallAsset.Succeeded())
	{
		m_SkillClassArray.Add(IceWallAsset.Class);
	}
	static ConstructorHelpers::FClassFinder<ASkillRange> IceWallRangeAsset(TEXT("Blueprint'/Game/UI/SkillRange/BP_IceWall.BP_IceWall_C'"));
	if (IceWallRangeAsset.Succeeded())
	{
		m_SkillRangeClassArray.Add(IceWallRangeAsset.Class);
	}
	
	static ConstructorHelpers::FClassFinder<ASkill> FireBallAsset(TEXT("Blueprint'/Game/Effect/Skill/BP_FireBall.BP_FireBall_C'"));
	if (FireBallAsset.Succeeded())
	{
		m_SkillClassArray.Add(FireBallAsset.Class);
	}

	static ConstructorHelpers::FClassFinder<ASkillRange> FireBallRangeAsset(TEXT("Blueprint'/Game/UI/SkillRange/BP_FiraBall.BP_FiraBall_C'"));
	if (FireBallRangeAsset.Succeeded())
	{
		m_SkillRangeClassArray.Add(FireBallRangeAsset.Class);
	}

	m_AttackIndex = 0;
	m_PlayerInfoName = TEXT("Phase");
	m_SkillRange = nullptr;
}

// Called when the game starts or when spawned
void APhase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APhase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APhase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void APhase::AttackAnim()
{
	if (!m_AnimInstance->Montage_IsPlaying(m_AttackMontageArray[m_AttackIndex]))
	{
		m_AnimInstance->Montage_SetPosition(m_AttackMontageArray[m_AttackIndex], 0.f);
		m_AnimInstance->Montage_Play(m_AttackMontageArray[m_AttackIndex]);
		m_AnimInstance->SetAttack(true);

		//m_AttackIndex = (m_AttackIndex + 1) % m_AttackMontageArray.Num();
	}
}


void APhase::SkillAnim(int8 SkillIdx)
{
	if (m_SkillRange)
	{
		m_SkillRange->Destroy();
		m_SkillRange = nullptr;
	}

	if (!m_AnimInstance->Montage_IsPlaying(m_SkillMontageArray[SkillIdx]))
	{
		m_AnimInstance->Montage_SetPosition(m_SkillMontageArray[SkillIdx], 0.f);
		m_AnimInstance->Montage_Play(m_SkillMontageArray[SkillIdx]);
		m_AnimInstance->SetAttack(true);
		m_AnimInstance->SetSkillIdx(SkillIdx);
	}
}

void APhase::NormalAttack()
{
	/*FVector MuzzleLoc = GetMesh()->GetSocketLocation(TEXT("Muzzle_01"));
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ASkill* FireBall = GetWorld()->SpawnActor<ASkill>(m_SkillClassArray[0], MuzzleLoc, GetActorRotation(), param);
	FireBall->SetSkillOwner(this);
	FireBall->SetAttack(m_PlayerInfo.Attack);*/
}


void APhase::Skill(int8 SkillIdx)
{
	

	FVector SpawnLoc;
	if (0 == SkillIdx)
	{
		SpawnLoc = GetMesh()->GetSocketLocation(TEXT("ik_foot_root"));
	}
	else if (1 == SkillIdx)
	{
		SpawnLoc = GetMesh()->GetSocketLocation(TEXT("Muzzle_01"));
	}

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ASkill* Skill = GetWorld()->SpawnActor<ASkill>(m_SkillClassArray[SkillIdx], SpawnLoc, GetActorRotation(), param);

	Skill->SetSkillOwner(this);
	Skill->SetAttack(m_PlayerInfo.Attack);
}

void APhase::AttackEnd()
{

}


void APhase::SkillReady(int8 SkillIdx)
{	
	if (m_SkillRange)
	{
		m_SkillRange->Destroy();
		m_SkillRange = nullptr;
	}

	if (0 <= SkillIdx && SkillIdx < m_SkillRangeClassArray.Num())
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		m_SkillRange = GetWorld()->SpawnActor<ASkillRange>(m_SkillRangeClassArray[SkillIdx], FVector::ZeroVector, FRotator::ZeroRotator, param);
	}
}
