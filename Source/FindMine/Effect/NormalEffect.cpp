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

	// ����ƼŬ�ý���������Ʈ�� ������ �մ� ����ƼŬ�ý����� ����� ��� ���ᰡ �Ǿ��� ���

	// Dynamice, Multicast, single, ���ڿ����� �ٸ��� �Ǿ��ִ�
	if (!m_AssetLoop)
		m_ParticleSystem->OnSystemFinished.AddDynamic(this, &ANormalEffect::ParticleFinish);	//��������Ʈ�� �̷�����յ� ��������Ʈ�� ��� �ൿ�� ������ ������ �Լ��� ȣ���ϴ°�
}

// Called every frame
void ANormalEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANormalEffect::LoadParticle(const FString& Path)
{
	UParticleSystem* Particle = LoadObject<UParticleSystem>(GetWorld(), *Path);		//��Ÿ�� ��ü ���鋚��� �ַ� ���¸��鶧 ����Ѵ�
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

	FStreamableManager& streamMgr = UAssetManager::GetStreamableManager();	//engine�̰� �����ִ� assetm manger�� ������

	m_AsyncParticleLoadHandle = streamMgr.RequestAsyncLoad(m_AsyncParticlePath	//�񵿱� �ε尡 ������ ȣ��� �Լ��� �������ش�. ���������� ��������Ʈ�� �����Ǿ�����
								, FStreamableDelegate::CreateUObject(this, &ANormalEffect::LoadParticleAsyncComplete));	//��������Ʈ�� ���� �Ѱ��ش�
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

	FStreamableManager& streamMgr = UAssetManager::GetStreamableManager();	//engine�̰� �����ִ� assetm manger�� ������

	m_AsyncSoundLoadHandle = streamMgr.RequestAsyncLoad(m_AsyncSoundPath	//�񵿱� �ε尡 ������ ȣ��� �Լ��� �������ش�. ���������� ��������Ʈ�� �����Ǿ�����
		, FStreamableDelegate::CreateUObject(this, &ANormalEffect::LoadSoundAsyncComplete));	//��������Ʈ�� ���� �Ѱ��ش�
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