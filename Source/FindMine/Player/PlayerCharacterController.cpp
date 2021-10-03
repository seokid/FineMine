// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "PlayerCharacter.h"

APlayerCharacterController::APlayerCharacterController()
{
	bShowMouseCursor = true;
	m_bLButtonPress = false;
	m_bRButtonPress = false;

	m_InputState = EInputState::End;
}


void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("LButton"), EInputEvent::IE_Pressed, this, &APlayerCharacterController::LButtonPress);
	InputComponent->BindAction(TEXT("LButton"), EInputEvent::IE_Released, this, &APlayerCharacterController::LButtonRelease);

	InputComponent->BindAction(TEXT("RButton"), EInputEvent::IE_Pressed, this, &APlayerCharacterController::RButtonPress);
	InputComponent->BindAction(TEXT("RButton"), EInputEvent::IE_Released, this, &APlayerCharacterController::RButtonRelease);

	InputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Released, this, &APlayerCharacterController::AttackButtonRelease);
	InputComponent->BindAction(TEXT("Skill1"), EInputEvent::IE_Released, this, &APlayerCharacterController::Skill1ButtonRelease);
	InputComponent->BindAction(TEXT("Skill2"), EInputEvent::IE_Released, this, &APlayerCharacterController::Skill2ButtonRelease);
	InputComponent->BindAction(TEXT("Skill3"), EInputEvent::IE_Released, this, &APlayerCharacterController::Skill3ButtonRelease);
	InputComponent->BindAction(TEXT("Skill4"), EInputEvent::IE_Released, this, &APlayerCharacterController::Skill4ButtonRelease);
}


void APlayerCharacterController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (m_bRButtonPress)
	{
		RButtonDown();
	}

}

void APlayerCharacterController::LootAt(AActor* Actor, FVector Location)
{
	Location -= Actor->GetActorLocation();
	Location.Normalize();
	Actor->SetActorRotation(FRotator(0.f, Location.Rotation().Yaw, 0.f));
}


void APlayerCharacterController::LButtonPress()
{
	m_bLButtonPress = true;
}

void APlayerCharacterController::LButtonRelease()
{
	if (m_bLButtonPress)
		LButtonClick();


	m_bLButtonPress = false;

}


void APlayerCharacterController::LButtonClick()
{

	FHitResult result;
	bool Hit = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel8, false, result);	//복합충돌 여부 = false

	if (Hit)
	{
		if (EInputState::Skill1 <= m_InputState && m_InputState < EInputState::SkillEnd)
		{
			APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
			if (PlayerCharacter)
			{
				PlayerCharacter->SkillEvent((uint8)m_InputState - (uint8)EInputState::Skill1);
				StopMovement();
				LootAt(GetPawn(), result.ImpactPoint);
			}
		}
		/*if (EInputState::Attack == m_InputState)
		{
			APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
			if (PlayerCharacter)
			{
				PlayerCharacter->AttackEvent();
				StopMovement();
				LootAt(GetPawn(), result.ImpactPoint);
			}
		}*/
	
	}
	
	m_InputState = EInputState::End;	
}

void APlayerCharacterController::RButtonPress()
{
	m_bRButtonPress = true;
}

void APlayerCharacterController::RButtonRelease()
{
	if (m_bRButtonPress)
		RButtonClick();

	m_bRButtonPress = false;

}

void APlayerCharacterController::RButtonDown()
{
	
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		if (PlayerCharacter->IsAttack())
			return;
		
	}

	FHitResult result;
	bool Hit = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel8, false, result);	//복합충돌 여부 = false

	m_InputState = EInputState::Move;

	if (Hit)
	{
		//m_SelectCharacter->GetCharacterMovement()->MaxWalkSpeed = m_SelectCharacter->PlayerInfo;
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, result.ImpactPoint);
	}
}

void APlayerCharacterController::RButtonClick()
{

}

void APlayerCharacterController::AttackButtonRelease()
{
	m_InputState = EInputState::Attack;

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		PlayerCharacter->SkillReadyEvent(0);

		//if (m_SkillRangeClass)
		//{
		//	FActorSpawnParameters param;
		//	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//	m_SkillRange = GetWorld()->SpawnActor<ASkillRange>(m_SkillRangeClass, FVector::ZeroVector, FRotator::ZeroRotator, param);
		//}
	}
}


void APlayerCharacterController::SkillSetting(int8 SkillIdx)
{
	m_InputState = (EInputState)((int8)EInputState::Skill1 + (int8)SkillIdx);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		PlayerCharacter->SkillReadyEvent(SkillIdx);
	}
}


void APlayerCharacterController::Skill1ButtonRelease()
{
	SkillSetting(0);
}

void APlayerCharacterController::Skill2ButtonRelease()
{
	SkillSetting(1);
}

void APlayerCharacterController::Skill3ButtonRelease()
{
	SkillSetting(2);
}

void APlayerCharacterController::Skill4ButtonRelease()
{
	SkillSetting(3);
}
