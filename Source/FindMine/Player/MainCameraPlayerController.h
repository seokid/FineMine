// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "MainCameraPlayerController.generated.h"


UCLASS()
class FINDMINE_API AMainCameraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainCameraPlayerController();

protected:
	class APlayerCharacter*	m_SelectCharacter;
	AActor*	m_MainCamera;
	bool	m_bLButtonPress;
	bool	m_bRButtonPress;
	bool	m_bAttackPress;

public:
	virtual void PlayerTick(float DeltaTime);
	virtual void SetupInputComponent();

private:
	void LButtonPress();
	void LButtonRelease();
	void LButtonClick();

	void RButtonPress();
	void RButtonRelease();
	void RButtonDown();
	void RButtonClick();
};
