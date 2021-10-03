// Fill out your copyright notice in the Description page of Project Settings.


#include "FindMineGameInstance.h"


UFindMineGameInstance::UFindMineGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterInfotableAsset(TEXT("DataTable'/Game/Monster/DT_MonsterInfo.DT_MonsterInfo'"));

	if (MonsterInfotableAsset.Succeeded())
	{
		m_MonsterInfoTable = MonsterInfotableAsset.Object;
	}


	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerInfotableAsset(TEXT("DataTable'/Game/Player/DT_PlayerInfo.DT_PlayerInfo'"));

	if (PlayerInfotableAsset.Succeeded())
	{
		m_PlayerInfoTable = PlayerInfotableAsset.Object;
	}


	static ConstructorHelpers::FObjectFinder<UDataTable> SkillInfotableAsset(TEXT("DataTable'/Game/Effect/Skill/DT_SkillInfo.DT_SkillInfo'"));

	if (SkillInfotableAsset.Succeeded())
	{
		m_SkillInfoTable = SkillInfotableAsset.Object;
	}
}


void UFindMineGameInstance::Init()
{
	Super::Init();


}

const FMonsterTableInfo* UFindMineGameInstance::FindMonsterInfo(const FString& Name)
{
	return m_MonsterInfoTable->FindRow<FMonsterTableInfo>(*Name, "");
}


const FPlayerTableInfo* UFindMineGameInstance::FindPlayerInfo(const FString& Name)
{
	return m_PlayerInfoTable->FindRow<FPlayerTableInfo>(*Name, "");
}

const FSkillTableInfo* UFindMineGameInstance::FindSkillInfo(const FString& Name)
{
	return m_SkillInfoTable->FindRow<FSkillTableInfo>(*Name, "");
}