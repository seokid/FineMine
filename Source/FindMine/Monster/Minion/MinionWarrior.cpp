// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionWarrior.h"
#include "../../Effect/NormalEffect.h"

AMinionWarrior::AMinionWarrior()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WarriorAsset(TEXT("SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Down_Minions/Meshes/Minion_Lane_Melee_Dawn.Minion_Lane_Melee_Dawn'"));

	if (WarriorAsset.Succeeded())// �ε�����
	{
		GetMesh()->SetSkeletalMesh(WarriorAsset.Object);	//CharactorŬ������ ��������մ� SkeletalMeshComponent�� ������ �Լ�
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> WarriorAnimAsset(TEXT("AnimBlueprint'/Game/Monster/Minion/ABP_MinionWarrior.ABP_MinionWarrior_C'"));

	if (WarriorAnimAsset.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(WarriorAnimAsset.Class);
	}

	m_MonsterInfoName = TEXT("MinionWarrior");

}

// Called when the game starts or when spawned
void AMinionWarrior::BeginPlay()
{
	GetMesh()->CreateDynamicMaterialInstance(0);	//0���� �����Ǿ��ִ� ���׸����� ���̳������� �ٲ��ش�
													//������ ���׸��� ���� �θ𿡼� �������ټ��ֱ⶧���� �θ� ���� ���� ����
	Super::BeginPlay();

}

// Called every frame
void AMinionWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMinionWarrior::NormalAttack()
{
	FVector MinionLoc = GetActorLocation();	//���� ��ġ
	FVector Forward = GetActorForwardVector();

	FCollisionQueryParams params(NAME_None, false, this);	//�����浹 false

	//���� �������� �� Ÿ�ֿ̹� �浹ó���� ���ֵ��� �Ѵ�.
	FHitResult result;	//�浹ó�� ����� �����ϴ� ����ü, faceidx �ε��� �ﰢ�� �ε���, ImpacPoint �ε��� ��ġ, Normal �ε��� ����

	//Single�� �Ѹ�, Multi�� ������, Over�� ��ħ��  
	bool Sweep = GetWorld()->SweepSingleByChannel(result
		, MinionLoc	//������ġ
		, MinionLoc + Forward * m_MonsterInfo.AttackDistance	//���ݹ���
		, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel7
		, FCollisionShape::MakeSphere(30.f), params);

	FHitResult CollisionArray = {};

#if ENABLE_DRAW_DEBUG
	FColor DrawColor = Sweep ? FColor::Red : FColor::Green;

	FVector Center = MinionLoc + Forward * (m_MonsterInfo.AttackDistance / 2.f);
	//DrawDebugSphere(GetWorld(), PlayerLoc, m_PlayerInfo.AttackDistance, 20, DrawColor, false, 1.f);
	DrawDebugCapsule(GetWorld(), Center, m_MonsterInfo.AttackDistance / 2.f
		, 30.f, FRotationMatrix::MakeFromZ(Forward).ToQuat()
		, DrawColor, false, 0.5f);
#endif

	if (Sweep)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;	//�ٷ� ��ȯ, �ٸ��� �������������������� ��ȯ���ִ°͵��մ�
		ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), result.ImpactPoint, result.ImpactNormal.Rotation(), param);

		Effect->LoadParticleAsync(TEXT("Hit_Lightning"));
		//������ ����
		FDamageEvent DmgEvent = {};

		result.GetActor()->TakeDamage(m_MonsterInfo.Attack, DmgEvent, GetController(), this);	//���ݷ�, �̺�Ʈ����, ��Ʈ�ѷ�, ���� �����°�
	}
}