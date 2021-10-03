// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionAIController.h"

AMinionAIController::AMinionAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AITreeAsset(TEXT("BehaviorTree'/Game/Monster/Minion/BT_Minion.BT_Minion'"));
	if (AITreeAsset.Succeeded())
		m_AITree = AITreeAsset.Object;
		

	static ConstructorHelpers::FObjectFinder<UBlackboardData> AIBlackboardAsset(TEXT("BlackboardData'/Game/Monster/BB_Monster.BB_Monster'"));
	if (AIBlackboardAsset.Succeeded())
		m_AIBalckboard = AIBlackboardAsset.Object;
}


void AMinionAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AMinionAIController::OnUnPossess()
{
	Super::OnUnPossess();

}