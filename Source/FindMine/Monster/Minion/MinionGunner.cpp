// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionGunner.h"

AMinionGunner::AMinionGunner()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WarriorAsset(TEXT("SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Down_Minions/Meshes/Minion_Lane_Ranged_Dawn.Minion_Lane_Ranged_Dawn'"));

	if (WarriorAsset.Succeeded())// 로딩성공
	{
		GetMesh()->SetSkeletalMesh(WarriorAsset.Object);	//Charactor클래스에 만들어져잇는 SkeletalMeshComponent를 얻어오는 함수
	}

	/*static ConstructorHelpers::FClassFinder<UAnimInstance> WarriorAnimAsset(TEXT("AnimBlueprint'/Game/Monster/ABP_MinionWarrior.ABP_MinionWarrior_C'"));

	if (WarriorAnimAsset.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(WarriorAnimAsset.Class);
	}*/

	m_MonsterInfoName = TEXT("MinionGunner");
}

// Called when the game starts or when spawned
void AMinionGunner::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMinionGunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}