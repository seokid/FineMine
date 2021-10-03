// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBall.h"
#include "../NormalEffect.h"

AFireBall::AFireBall()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Asset(TEXT("ParticleSystem'/Game/Luos8Elements/Particles/Fire/Par_LMagic_Fire_Atk_01.Par_LMagic_Fire_Atk_01'"));

	if (Asset.Succeeded())
		m_Particle->SetTemplate(Asset.Object);
	
	m_Movement->InitialSpeed = 2000.f;
	m_SkillInfoName = TEXT("FireBall");
}
// Called when the game starts or when spawned
void AFireBall::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AFireBall::StopEvent(const FHitResult& result)
{
	Super::StopEvent(result);

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;	//바로 소환, 다른건 겹쳐잇지않은지점에서 소환해주는것도잇다
	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), result.ImpactPoint, result.Normal.Rotation(), param);

	Effect->LoadParticle(TEXT("ParticleSystem'/Game/Luos8Elements/Particles/Fire/Par_LMagic_Fire_Explosion.Par_LMagic_Fire_Explosion'"));
	//Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Fire4.Fire4'"));

	m_Particle->DestroyComponent();


	FDamageEvent DmgEvent = {};
	result.GetActor()->TakeDamage(m_Attack * m_SkillInfo.DamagePer, DmgEvent, m_SkillOwner->GetController(), m_SkillOwner);	//공격력, 이벤트정보, 컨트롤러, 누가 때리는가
}