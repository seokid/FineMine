// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"

AMonsterAIController::AMonsterAIController()
{

}


void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//�����带 ����
	if (UseBlackboard(m_AIBalckboard, Blackboard))
	{
		//�ൿƮ���� ����
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