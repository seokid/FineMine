// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TargetTrace.h"

#include "../Monster/Monster.h"
#include "../Monster/MonsterAIController.h"
#include "../Player/PlayerCharacter.h"

UBTTask_TargetTrace::UBTTask_TargetTrace()
{
	NodeName = TEXT("TargetTrace");
	bNotifyTick = true;
}


EBTNodeResult::Type UBTTask_TargetTrace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	// ���ݰŸ� �ȿ� ���Դ��� ���⼭�� üũ�Ͽ� ���ٸ� Trace�� �����Ų��
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!Controller)
	{
		return EBTNodeResult::Failed;
	}

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	if (!Monster)
	{
		return EBTNodeResult::Failed;
	}

	APlayerCharacter* Target = Cast<APlayerCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!Target)
	{
		Monster->ChangeAnimType(EMonsterAnimType::Idle);
		Controller->StopMovement();
		return EBTNodeResult::Failed;
	}
	const FMonsterInfo& MonsterInfo = Monster->GetMonsterInfo();
	Monster->GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.MoveSpeed;
	Monster->ChangeAnimType(EMonsterAnimType::Run);
	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);	//������ ��ġ�� �̵�

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_TargetTrace::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::AbortTask(OwnerComp, NodeMemory);
	return result;
}

void UBTTask_TargetTrace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// InProgress�� �صξ��� ������ ���⼭ �ȳ�����.
	// ���ݰŸ� �ȿ� ���Դ��� ���⼭�� üũ�Ͽ� ���ٸ� Trace�� �����Ų��
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!Controller)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}


	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	if (!Monster)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	APlayerCharacter* Target = Cast<APlayerCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!Target)
	{
		Monster->ChangeAnimType(EMonsterAnimType::Idle);
		Controller->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	const FMonsterInfo& MonsterInfo = Monster->GetMonsterInfo();


	FVector MonsterLoc = Monster->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();
	MonsterLoc.Z = TargetLoc.Z;

	float Distance = FVector::Distance(MonsterLoc, TargetLoc);

	if (Distance <= MonsterInfo.AttackDistance)
	{
		Controller->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}