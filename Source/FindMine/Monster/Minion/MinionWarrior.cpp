// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionWarrior.h"
#include "../../Effect/NormalEffect.h"

AMinionWarrior::AMinionWarrior()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WarriorAsset(TEXT("SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Down_Minions/Meshes/Minion_Lane_Melee_Dawn.Minion_Lane_Melee_Dawn'"));

	if (WarriorAsset.Succeeded())// 로딩성공
	{
		GetMesh()->SetSkeletalMesh(WarriorAsset.Object);	//Charactor클래스에 만들어져잇는 SkeletalMeshComponent를 얻어오는 함수
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
	GetMesh()->CreateDynamicMaterialInstance(0);	//0번에 설정되어있는 메테리얼을 다이나믹으로 바꿔준다
													//생성된 메테리얼에 대해 부모에서 설정해줄수있기때문에 부모 보다 먼저 설정
	Super::BeginPlay();

}

// Called every frame
void AMinionWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMinionWarrior::NormalAttack()
{
	FVector MinionLoc = GetActorLocation();	//몬스터 위치
	FVector Forward = GetActorForwardVector();

	FCollisionQueryParams params(NAME_None, false, this);	//복합충돌 false

	//근접 공격으로 이 타이밍에 충돌처리를 해주도록 한다.
	FHitResult result;	//충돌처리 결과를 저장하는 구조체, faceidx 부딪힌 삼각형 인덱스, ImpacPoint 부딪힌 위치, Normal 부딪힌 방향

	//Single은 한명만, Multi는 여러명, Over는 겹침만  
	bool Sweep = GetWorld()->SweepSingleByChannel(result
		, MinionLoc	//시작위치
		, MinionLoc + Forward * m_MonsterInfo.AttackDistance	//공격범위
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
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;	//바로 소환, 다른건 겹쳐잇지않은지점에서 소환해주는것도잇다
		ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), result.ImpactPoint, result.ImpactNormal.Rotation(), param);

		Effect->LoadParticleAsync(TEXT("Hit_Lightning"));
		//데미지 전달
		FDamageEvent DmgEvent = {};

		result.GetActor()->TakeDamage(m_MonsterInfo.Attack, DmgEvent, GetController(), this);	//공격력, 이벤트정보, 컨트롤러, 누가 때리는가
	}
}