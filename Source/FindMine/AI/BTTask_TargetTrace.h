// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TargetTrace.generated.h"

/**
 * 
 */
UCLASS()
class FINDMINE_API UBTTask_TargetTrace : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_TargetTrace();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);	//테스크 실행
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);		//테스크 중단
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);	//매틱마다 들어옴
};
