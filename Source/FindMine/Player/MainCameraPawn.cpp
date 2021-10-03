// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCameraPawn.h"
#include "CameraPawnMovementComponent.h"

// Sets default values
AMainCameraPawn::AMainCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SetRootComponent(m_Camera);
	
	m_Camera->SetRelativeLocation(FVector(0.f, 0.f, 1000.f));
	m_Camera->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

	m_MovementComponent = CreateDefaultSubobject<UCameraPawnMovementComponent>(TEXT("MovementComponent"));
	m_MovementComponent->UpdatedComponent = RootComponent;
	m_MovementComponent->SetMoveSpeed(1000.f);
}

// Called when the game starts or when spawned
void AMainCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("CameraSideMove"), this, &AMainCameraPawn::CameraSideMove);
	PlayerInputComponent->BindAxis(TEXT("CameraUpMove"), this, &AMainCameraPawn::CameraUpMove);
}

void AMainCameraPawn::CameraSideMove(float Scale)
{
	if (m_MovementComponent && (m_MovementComponent->UpdatedComponent == RootComponent))
	{
		m_MovementComponent->AddInputVector(GetActorRightVector() * Scale);
	}
}
void AMainCameraPawn::CameraUpMove(float Scale)
{
	if (m_MovementComponent && (m_MovementComponent->UpdatedComponent == RootComponent))
	{
		FVector vec = GetActorUpVector();
		vec.Z = 0.f;
		vec.Normalize();
		m_MovementComponent->AddInputVector(vec * Scale);
	}
}


UPawnMovementComponent* AMainCameraPawn::GetMovementComponent() const
{
	return m_MovementComponent;
}
