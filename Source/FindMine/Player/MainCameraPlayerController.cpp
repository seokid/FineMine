// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCameraPlayerController.h"
#include "PlayerCharacter.h"
#include "../Monster/Monster.h"

AMainCameraPlayerController::AMainCameraPlayerController()
{
	bShowMouseCursor = true;
	m_bLButtonPress = false;
	m_bRButtonPress = false;
	m_SelectCharacter = nullptr;
}


void AMainCameraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("LButton"), EInputEvent::IE_Pressed, this, &AMainCameraPlayerController::LButtonPress);
	InputComponent->BindAction(TEXT("LButton"), EInputEvent::IE_Released, this, &AMainCameraPlayerController::LButtonRelease);

	InputComponent->BindAction(TEXT("RButton"), EInputEvent::IE_Pressed, this, &AMainCameraPlayerController::RButtonPress);
	InputComponent->BindAction(TEXT("RButton"), EInputEvent::IE_Released, this, &AMainCameraPlayerController::RButtonRelease);
}


void AMainCameraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (m_bRButtonPress)
	{
		RButtonDown();
	}


	if (m_SelectCharacter)
	{
		int32 CurPathIdx = UAIBlueprintHelperLibrary::GetCurrentPathIndex(this);
		if (0 <= CurPathIdx)
		{
			const TArray<FVector>& Path = UAIBlueprintHelperLibrary::GetCurrentPathPoints(this);
			FVector Dir = Path[CurPathIdx];
			Dir -= GetPawn()->GetActorLocation();
			Dir.Normalize();
			PrintViewport(0.5f, FColor::Red, TEXT("LootAt"));
			GetPawn()->SetActorRotation(FRotator(0.f, Dir.Rotation().Yaw, 0.f));
		}
	}
	
}


void AMainCameraPlayerController::LButtonPress()
{
	m_bLButtonPress = true;
	
}

void AMainCameraPlayerController::LButtonRelease()
{
	if (m_bLButtonPress)
		LButtonClick();

	m_bLButtonPress = false;
	
}


void AMainCameraPlayerController::LButtonClick()
{


	
	
	FHitResult result;
	bool Hit = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, result);	//복합충돌 여부 = false
	if (Hit)
	{
		APlayerCharacter* SelectPlayer = Cast<APlayerCharacter>(result.GetActor());
		if (SelectPlayer)
		{
			m_SelectCharacter = SelectPlayer;
		}
	}
	
	
}


void AMainCameraPlayerController::RButtonPress()
{
	m_bRButtonPress = true;
}

void AMainCameraPlayerController::RButtonRelease()
{
	if (m_bRButtonPress)
		RButtonClick();

	m_bRButtonPress = false;

}


void AMainCameraPlayerController::RButtonDown()
{
	FHitResult result;
	bool Hit = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, result);	//복합충돌 여부 = false

	if (Hit)
	{
		if (m_SelectCharacter)
		{
			//m_SelectCharacter->GetCharacterMovement()->MaxWalkSpeed = m_SelectCharacter->PlayerInfo;
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(m_SelectCharacter->GetController(), result.ImpactPoint);	
		}
	}
}

void AMainCameraPlayerController::RButtonClick()
{
	
}
