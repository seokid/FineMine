// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "../FindMineGameInstance.h"
#include "../FindMineGameModeBase.h"
// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	m_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	m_Arm->SetupAttachment(RootComponent);

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Camera->SetupAttachment(m_Arm);

	GetCharacterMovement()->bOrientRotationToMovement = true;	//이동 방향에 맞게 회전
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	m_Arm->SetUsingAbsoluteRotation(true);
	m_Arm->TargetArmLength = 1200.0f;
	m_Arm->SetRelativeRotation(FRotator(-35.0f, 45.0f, 0.0f));
	m_Arm->bDoCollisionTest = false;

	m_Camera->bUsePawnControlRotation = false;
	m_bDeath = false;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	GetMesh()->bReceivesDecals = false;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	m_AnimInstance = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());

	UFindMineGameInstance* GameInst = Cast<UFindMineGameInstance>(GetWorld()->GetGameInstance());	//생성자에 구현하지 않은이유가 어떤 월드에 들어가있을지 모르기때문에 여기서구현

	if (GameInst)
	{
		const FPlayerTableInfo* Info = GameInst->FindPlayerInfo(m_PlayerInfoName);	//없을시 nullptr리턴
		if (Info)
		{
			m_PlayerInfo.Name = Info->Name;
			m_PlayerInfo.Job = Info->Job;
			m_PlayerInfo.Attack = Info->Attack;
			m_PlayerInfo.Armor = Info->Armor;
			m_PlayerInfo.AttackAngle = Info->AttackAngle;
			m_PlayerInfo.AttackDistance = Info->AttackDistance;
			m_PlayerInfo.AttackSpeed = Info->AttackSpeed;
			m_PlayerInfo.MoveSpeed = Info->MoveSpeed;
			m_PlayerInfo.Exp = Info->Exp;
			m_PlayerInfo.Gold = Info->Gold;
			m_PlayerInfo.HP = Info->HP;
			m_PlayerInfo.HPMax = Info->HPMax;
			m_PlayerInfo.Level = Info->Level;
			m_PlayerInfo.MP = Info->MP;
			m_PlayerInfo.MPMax = Info->MPMax;
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (0.f == Damage)
		return 0.f;

	Damage = Damage - m_PlayerInfo.Armor;
	Damage = Damage < 1.f ? 1.f : Damage;
	m_PlayerInfo.HP -= Damage;

	if (0 >= m_PlayerInfo.HP)
	{
		m_bDeath = true;
		//m_AnimInstance->ChangeAnimType(EPlayerAnimType::Death);
	}

	//GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(UHitCameraShake::StaticClass());

	/*if (IsValid(m_HPBarWidget))
	{
		m_HPBarWidget->SetHPPercent(m_PlayerInfo.HP / (float)m_PlayerInfo.HPMax);
	}*/

	AFindMineGameModeBase* GameMode = Cast<AFindMineGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!IsValid(GameMode))
		return Damage;

	/*UMainHUD* MainHUD = GameMode->GetMainHUD();
	if (!IsValid(MainHUD))
		return Damage;

	UCharacterHUD* CharacterHUD = MainHUD->GetCharacterHUD();
	if (!IsValid(CharacterHUD))
		return Damage;

	CharacterHUD->SetHPPercent(m_PlayerInfo.HP / (float)m_PlayerInfo.HPMax);*/

	return Damage;
}

void APlayerCharacter::AttackEvent()
{
	if (m_AnimInstance->IsAttack())
		return;

	AttackAnim();
}


void APlayerCharacter::SkillEvent(int8 SkillIdx)
{
	if (m_AnimInstance->IsAttack())
		return;

	SkillAnim(SkillIdx);
}


void APlayerCharacter::SkillReadyEvent(int8 SkillIdx)
{
	if (m_AnimInstance->IsAttack())
		return;

	SkillReady(SkillIdx);
}