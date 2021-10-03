// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PawnMovementComponent.h"
#include "CameraPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class FINDMINE_API UCameraPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	UCameraPawnMovementComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_MoveSpeed;

public:
	void SetMoveSpeed(float Speed) { m_MoveSpeed = Speed; }

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
