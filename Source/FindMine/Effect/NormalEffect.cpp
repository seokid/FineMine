// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalEffect.h"
#include "../AssetManager/AssetPathMain.h"
// Sets default values
ANormalEffect::ANormalEffect()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	SetRootComponent(m_ParticleSystem);

	m_AssetLoop = false;

}

// Called when the game starts or when spawned
void ANormalEffect::BeginPlay()
{
	Super::BeginPlay();

	// 이파티클시스템컴포넌트가 가지고 잇느 ㄴ파티클시스템이 재생이 모두 종료가 되엇을 경우

	// Dynamice, Multicast, single, 인자에따라 다르게 되어있다
	if (!m_AssetLoop)
		m_ParticleSystem->OnSystemFinished.AddDynamic(this, &ANormalEffect::ParticleFinish);	//델리게이트로 이뤄어져잇따 델리게이트는 어떠한 행동을 했을때 지정된 함수를 호출하는것
}

// Called every frame
void ANormalEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANormalEffect::LoadParticle(const FString& Path)
{
	UParticleSystem* Particle = LoadObject<UParticleSystem>(GetWorld(), *Path);		//런타임 객체 만들떄사용 주로 에셋만들때 사용한다
	if (Particle)
	{
		m_ParticleSystem->SetTemplate(Particle);
	}
}

void ANormalEffect::LoadParticleAsync(const FString& Name)
{
	UAssetPathMain* AssetPath = UAssetPathMain::StaticClass()->GetDefaultObject<UAssetPathMain>();
	const FSoftObjectPath* Path = AssetPath->FindParticlePath(Name);

	if (!Path)
		return;

	m_AsyncParticlePath = *Path;

	FStreamableManager& streamMgr = UAssetManager::GetStreamableManager();	//engine이가 지고있는 assetm manger를 가져옴

	m_AsyncParticleLoadHandle = streamMgr.RequestAsyncLoad(m_AsyncParticlePath	//비동기 로드가 끝나면 호출될 함수를 지정해준다. 내부적으로 델리게이트로 구현되어있음
								, FStreamableDelegate::CreateUObject(this, &ANormalEffect::LoadParticleAsyncComplete));	//델리게이트를 만들어서 넘겨준다
}

void ANormalEffect::LoadParticleAsyncComplete()
{
	m_AsyncParticleLoadHandle->ReleaseHandle();

	TAssetPtr<UParticleSystem> NewParticle(m_AsyncParticlePath);

	if (NewParticle)
	{
		m_ParticleSystem->SetTemplate(NewParticle.Get());
	}
}

void ANormalEffect::LoadSound(const FString& Path)
{
	USoundBase* Sound = LoadObject<USoundBase>(nullptr, *Path);

	if (Sound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());
}

void ANormalEffect::LoadSoundAsync(const FString& Name)
{
	UAssetPathMain* AssetPath = UAssetPathMain::StaticClass()->GetDefaultObject<UAssetPathMain>();
	AssetPath->ConvertPath();
	const FSoftObjectPath* Path = AssetPath->FindSoundPath(Name);

	if (!Path)
		return;

	m_AsyncSoundPath = *Path;

	FStreamableManager& streamMgr = UAssetManager::GetStreamableManager();	//engine이가 지고있는 assetm manger를 가져옴

	m_AsyncSoundLoadHandle = streamMgr.RequestAsyncLoad(m_AsyncSoundPath	//비동기 로드가 끝나면 호출될 함수를 지정해준다. 내부적으로 델리게이트로 구현되어있음
		, FStreamableDelegate::CreateUObject(this, &ANormalEffect::LoadSoundAsyncComplete));	//델리게이트를 만들어서 넘겨준다
}

void ANormalEffect::LoadSoundAsyncComplete()
{
	m_AsyncSoundLoadHandle->ReleaseHandle();

	TAssetPtr<USoundBase> NewSound(m_AsyncSoundPath);

	if (NewSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), NewSound.Get(), GetActorLocation());
	}
}

void ANormalEffect::ParticleFinish(UParticleSystemComponent* ParticleSystem)
{
	Destroy();
}