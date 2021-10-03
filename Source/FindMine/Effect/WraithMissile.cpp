// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithMissile.h"

AWraithMissile::AWraithMissile()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Asset(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Ambient/Fire/P_Env_Fire_Grate_01.P_Env_Fire_Grate_01'"));

	if (Asset.Succeeded())
		m_Particle->SetTemplate(Asset.Object);

	m_Movement->InitialSpeed = 2000.f;

}
// Called when the game starts or when spawned
void AWraithMissile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWraithMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AWraithMissile::StopEvent(const FHitResult& result)
{
	Super::StopEvent(result);

	//FActorSpawnParameters param;
	//param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;	//바로 소환, 다른건 겹쳐잇지않은지점에서 소환해주는것도잇다
	//ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), result.ImpactPoint, result.Normal.Rotation(), param);

	//Effect->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_stab.P_ky_stab'"));
	//Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Fire4.Fire4'"));

	//m_Particle->DestroyComponent();

	//if (IsValid(m_Owner))	//유효한지 확인
	//{
	//	FDamageEvent DmgEvent = {};
	//	result.GetActor()->TakeDamage(m_Owner->GetMonsterInfo().Attack, DmgEvent, m_Owner->GetController(), m_Owner);	//공격력, 이벤트정보, 컨트롤러, 누가 때리는가
	//}


}
