// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "../FindMineGameInstance.h"
#include "MonsterAIController.h"
#include "MonsterSpawnPoint.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_AnimInstance = nullptr;
	m_SpawnPoint = nullptr;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);		//메쉬는 충돌처리를 하지않겠다.
	GetMesh()->bReceivesDecals = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;			//둘다 가능하게

	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	m_PatrolIndex = 1;
	m_Dissolve = 0.f;
	m_DissolveFilter = 0.f;
	m_DissolveAccTime = 0.f;
	m_DissolveTime = 3.f;
	m_bDissolveEnable = false;
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	UFindMineGameInstance* GameInst = Cast<UFindMineGameInstance>(GetWorld()->GetGameInstance());	//생성자에 구현하지 않은이유가 어떤 월드에 들어가있을지 모르기때문에 여기서구현

	if (GameInst)
	{
		const FMonsterTableInfo* Info = GameInst->FindMonsterInfo(m_MonsterInfoName);	//없을시 nullptr리턴
		if (Info)
		{
			m_MonsterInfo.Name = Info->Name;
			m_MonsterInfo.Attack = Info->Attack;
			m_MonsterInfo.Armor = Info->Armor;
			m_MonsterInfo.AttackAngle = Info->AttackAngle;
			m_MonsterInfo.AttackDistance = Info->AttackDistance;
			m_MonsterInfo.AttackSpeed = Info->AttackSpeed;
			m_MonsterInfo.Exp = Info->Exp;
			m_MonsterInfo.Gold = Info->Gold;
			m_MonsterInfo.HP = Info->HP;
			m_MonsterInfo.HPMax = Info->HPMax;
			m_MonsterInfo.Level = Info->Level;
			m_MonsterInfo.MoveSpeed = Info->MoveSpeed;
			m_MonsterInfo.MP = Info->MP;
			m_MonsterInfo.MPMax = Info->MPMax;
			m_MonsterInfo.TraceDistance = Info->TraceDistance;
		}
	}


	m_AnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("DissolveEnable"), -1.f);

}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_bDissolveEnable)
	{
		m_DissolveAccTime += DeltaTime;

		if (m_DissolveAccTime >= m_DissolveTime)
		{
			m_DissolveAccTime = m_DissolveTime;

			m_Dissolve = 1.f;

			GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Dissolve"), m_Dissolve);
			Destroy();
			m_SpawnPoint->Death();
		}
		else
		{
			m_Dissolve = m_DissolveAccTime / m_DissolveTime;
			GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Dissolve"), m_Dissolve);
		}
	}
}

void AMonster::NormalAttack()
{
	
}

float AMonster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (0.f == Damage)
		return 0.f;

	Damage = Damage - m_MonsterInfo.Armor;
	Damage = Damage < 1.f ? 1.f : Damage;
	m_MonsterInfo.HP -= Damage;
	PrintViewport(1.f, FColor::Red, FString::Printf(TEXT("%d"), m_MonsterInfo.HP));
	if (0 >= m_MonsterInfo.HP)
	{
		m_bDissolveEnable = true;
		GetMesh()->SetScalarParameterValueOnMaterials(TEXT("DissolveEnable"), 1.f);
		
		m_AnimInstance->ChangeAnimType(EMonsterAnimType::Death);
		
		AMonsterAIController* MonsterController = Cast<AMonsterAIController>(GetController());

		if (MonsterController)
		{
			MonsterController->BrainComponent->StopLogic(TEXT("Dead"));
			MonsterController->StopMovement();
		}

	}
	else
	{
		m_AnimInstance->SetHit(1.f);
	}


	//if (IsValid(m_HPBarWidget))
	//{
	//	m_HPBarWidget->SetHPPercent(m_MonsterInfo.HP / (float)m_MonsterInfo.HPMax);
	//}



	return Damage;
}

void AMonster::Death()
{
	
}
