// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"

AMonsterAIController::AMonsterAIController()
{

}


void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//블랙보드를 지정
	if (UseBlackboard(m_AIBalckboard, Blackboard))
	{
		//행동트리를 동작
		if (!RunBehaviorTree(m_AITree))
		{
			LOG(TEXT("Minion BehaviorTree Error!!"));
		}
	}
}
void AMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();

}