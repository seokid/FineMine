// Fill out your copyright notice in the Description page of Project Settings.


#include "Wraith.h"
#include "SelectPlayerController.h"


AWraith::AWraith()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WraithAsset(TEXT("SkeletalMesh'/Game/ParagonWraith/Characters/Heroes/Wraith/Skins/ODGreen/Meshes/Wraith_ODGreen.Wraith_ODGreen'"));

	if (WraithAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(WraithAsset.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> WraithAnimAsset(TEXT("AnimBlueprint'/Game/Player/ABP_Wraith.ABP_Wraith_C'"));

	if (WraithAnimAsset.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(WraithAnimAsset.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackAsset(TEXT("AnimMontage'/Game/Player/AM_WraithAttack.AM_WraithAttack'"));

	if (AttackAsset.Succeeded())
	{
		m_AttackMontageArray.Add(AttackAsset.Object);
	}

	static ConstructorHelpers::FClassFinder<AActor> MissileClass(TEXT("Blueprint'/Game/Effect/BP_WraithMissile.BP_WraithMissile_C'"));

	if (MissileClass.Succeeded())
	{
		m_MissileClass = MissileClass.Class;
	}




	m_AttackIndex = 0;
	m_SkillIndex = 0;
	m_PlayerInfoName = TEXT("Wraith");
}

// Called when the game starts or when spawned
void AWraith::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWraith::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWraith::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AWraith::AttackAnim()
{
	if (!m_AnimInstance->Montage_IsPlaying(m_AttackMontageArray[m_AttackIndex]))
	{
		m_AnimInstance->Montage_SetPosition(m_AttackMontageArray[m_AttackIndex], 0.f);
		m_AnimInstance->Montage_Play(m_AttackMontageArray[m_AttackIndex]);
		m_AnimInstance->SetAttack(true);

		//m_AttackIndex = (m_AttackIndex + 1) % m_AttackMontageArray.Num();
	}
}

void AWraith::NormalAttack()
{
	FVector MuzzleLoc = GetMesh()->GetSocketLocation(TEXT("Muzzle_01"));
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AWraithMissile* Bullet = GetWorld()->SpawnActor<AWraithMissile>(m_MissileClass, MuzzleLoc, GetActorRotation(), param);
	//Bullet->SetMonsterOwner(this);
}

void AWraith::AttackEnd()
{

}