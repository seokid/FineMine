// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerDetect.h"
#include "../Monster/MonsterAIController.h"
#include "../Monster/Monster.h"
UBTService_PlayerDetect::UBTService_PlayerDetect()
{
	NodeName = TEXT("Detect");
	Interval = 0.5f;
}

void UBTService_PlayerDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!Controller)
		return;


	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());
	if (!Monster)
		return;


	
	const FMonsterInfo& MonsterInfo = Monster->GetMonsterInfo();


	FCollisionQueryParams params(NAME_None, false, Monster);	//�����浹 false


	FHitResult HitResult;	//�浹ó�� ����� �����ϴ� ����ü, faceidx �ε��� �ﰢ�� �ε���, ImpacPoint �ε��� ��ġ, Normal �ε��� ����

	//Single�� �Ѹ�, Multi�� ������, Over�� ��ħ��  
	bool Sweep = GetWorld()->SweepSingleByChannel(HitResult
		, Monster->GetActorLocation()
		, Monster->GetActorLocation()
		, FQuat::Identity	//ȸ�� �ʿ����
		, ECollisionChannel::ECC_GameTraceChannel3
		, FCollisionShape::MakeSphere(MonsterInfo.TraceDistance)
		, params);

#if ENABLE_DRAW_DEBUG
	FColor DrawColor = Sweep ? FColor::Red : FColor::Green;
	DrawDebugSphere(GetWorld(), Monster->GetActorLocation(), MonsterInfo.TraceDistance, 20, DrawColor, false, 0.3f);
#endif

	if (Sweep)
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), HitResult.GetActor());
	}
	else
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
	}
}