// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill.h"
#include "../FindMineGameInstance.h"

// Sets default values
ASkill::ASkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	SetRootComponent(m_Particle);
}

// Called when the game starts or when spawned
void ASkill::BeginPlay()
{
	Super::BeginPlay();
	UFindMineGameInstance* GameInst = Cast<UFindMineGameInstance>(GetWorld()->GetGameInstance());	//�����ڿ� �������� ���������� � ���忡 �������� �𸣱⶧���� ���⼭����

	if (GameInst)
	{
		const FSkillTableInfo* Info = GameInst->FindSkillInfo(m_SkillInfoName);	//������ nullptr����
		if (Info)
		{
			m_SkillInfo.Name = Info->Name;
			m_SkillInfo.DamagePer = Info->DamagePer;
			m_SkillInfo.CoolDown = Info->CoolDown;
			m_SkillInfo.UseMP = Info->UseMP;
			m_SkillInfo.Type = Info->Type;
			m_SkillInfo.Range = Info->Range;
			m_SkillInfo.Distance = Info->Distance;
			m_SkillInfo.Duration = Info->Duration;
		}
	}
	
}

// Called every frame
void ASkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

