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
	UFindMineGameInstance* GameInst = Cast<UFindMineGameInstance>(GetWorld()->GetGameInstance());	//생성자에 구현하지 않은이유가 어떤 월드에 들어가있을지 모르기때문에 여기서구현

	if (GameInst)
	{
		const FSkillTableInfo* Info = GameInst->FindSkillInfo(m_SkillInfoName);	//없을시 nullptr리턴
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

