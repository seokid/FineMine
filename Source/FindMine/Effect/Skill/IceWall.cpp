// Fill out your copyright notice in the Description page of Project Settings.


#include "IceWall.h"

AIceWall::AIceWall()
{
	PrimaryActorTick.bCanEverTick = true;

	m_Body = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	
	SetRootComponent(m_Body);
	m_Particle->SetupAttachment(m_Body);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Asset(TEXT("ParticleSystem'/Game/Luos8Elements/Particles/Ice/Par_4E_Ice_Def_01.Par_4E_Ice_Def_01'"));

	if (Asset.Succeeded())
		m_Particle->SetTemplate(Asset.Object);

	m_TickAccTime = 0.f;
	m_SkillInfoName = TEXT("IceWall");
}
// Called when the game starts or when spawned
void AIceWall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AIceWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_TickAccTime += DeltaTime;

	if (0.5f < m_TickAccTime)
	{
		FCollisionQueryParams params(NAME_None, false, this);	//복합충돌 false
		TArray<FOverlapResult> OverResults;
		//Single은 한명만, Multi는 여러명, Over는 겹침만  
		bool Over = GetWorld()->OverlapMultiByChannel(OverResults
			, GetActorLocation()	//시작위치
			, FQuat::Identity
			, ECollisionChannel::ECC_GameTraceChannel6
			, m_Body->GetCollisionShape(), params);
//
//
//#if ENABLE_DRAW_DEBUG
//		FColor DrawColor = Over ? FColor::Red : FColor::Green;
//		DrawDebugBox(GetWorld(), GetActorLocation(),m_Body->GetScaledBoxExtent(), DrawColor, false, 0.3f);
//#endif


		if (Over)
		{
			for (auto& result : OverResults)
			{	
				LOG(TEXT("Actor Name: %s"), *result.Actor->GetName());
				FDamageEvent DmgEvent = {};
				result.Actor->TakeDamage(m_Attack * m_SkillInfo.DamagePer, DmgEvent, m_SkillOwner->GetController(), m_SkillOwner);	//공격력, 이벤트정보, 컨트롤러, 누가 때리는가;
			}
		}
		m_TickAccTime = 0.f;
	}

}