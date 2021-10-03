// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "MonsterAnimInstance.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"



USTRUCT(BlueprintType)
struct FMonsterInfo
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString	Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	HPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	MPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	AttackAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	TraceDistance;
};


UCLASS()
class FINDMINE_API AMonster : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonster();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FMonsterInfo	m_MonsterInfo;
	FString			m_MonsterInfoName;
	class AMonsterSpawnPoint*	m_SpawnPoint;
	UMonsterAnimInstance*		m_AnimInstance;

	TArray<FVector>				m_PatrolArray;
	int32						m_PatrolIndex;

	bool						m_bAttackEnd;

	bool						m_bDissolveEnable;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float						m_DissolveFilter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float						m_DissolveTime;

	float						m_DissolveAccTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float						m_Dissolve;

public:

	const FVector& GetPatrolPoint() const
	{ 
		return m_PatrolArray[m_PatrolIndex]; 
	}

	EMonsterAnimType GetAnimType() const
	{
		return m_AnimInstance->GetAnimType(); 
	}

	const FMonsterInfo& GetMonsterInfo() const
	{
		return m_MonsterInfo; 
	}

	bool GetAttackEnd() 
	{
		return m_bAttackEnd;
	}

	void SetSpawnPoint(class AMonsterSpawnPoint* SpawnPoint) 
	{ 
		m_SpawnPoint = SpawnPoint; 
	}

	void SetAttackEnd(bool AttackEnd) 
	{ 
		m_bAttackEnd = AttackEnd;
	}


public:
	void NextPatrolPoint()
	{
		++m_PatrolIndex %= m_PatrolArray.Num();
	}

	void AddPatrolPoint(const FVector& Point)
	{
		m_PatrolArray.Add(Point);
	}

	void ChangeAnimType(EMonsterAnimType Type)
	{
		if (!m_AnimInstance)
			return;
		m_AnimInstance->ChangeAnimType(Type);
	}

public:
	void Death();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	virtual void NormalAttack();
};
