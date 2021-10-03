// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NormalAttack.h"

#include "../Monster/Monster.h"
#include "../Monster/MonsterAIController.h"
#include "../Player/PlayerCharacter.h"

UBTTask_NormalAttack::UBTTask_NormalAttack()
{
	NodeName = TEXT("NormalAttack");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_NormalAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	Monster->ChangeAnimType(EMonsterAnimType::Attack);

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_NormalAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::AbortTask(OwnerComp, NodeMemory);
	return result;
}

void UBTTask_NormalAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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


	if (Monster->GetAttackEnd())
	{
		if (Distance > MonsterInfo.AttackDistance)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		}
		else
		{
			FVector Dir = TargetLoc - MonsterLoc;
			Dir.Normalize();
			Monster->SetActorRotation(FRotator(0.f, Dir.Rotation().Yaw, 0.f));
		}
		Monster->SetAttackEnd(false);
		return;
	}



}