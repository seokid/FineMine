// Copyright Epic Games, Inc. All Rights Reserved.


#include "FindMineGameModeBase.h"
#include "Player/PlayerCharacterController.h"


AFindMineGameModeBase::AFindMineGameModeBase()
{

	ConstructorHelpers::FClassFinder<APawn> PawnClass(TEXT("Blueprint'/Game/Player/Phase/BP_Phase.BP_Phase_C'"));
	if (PawnClass.Succeeded())
	{
		DefaultPawnClass = PawnClass.Class;
	}

	PlayerControllerClass = APlayerCharacterController::StaticClass();

	m_MainAssetPath = UAssetPathMain::StaticClass()->GetDefaultObject<UAssetPathMain>();
	m_MainAssetPath->ConvertPath();
}

void AFindMineGameModeBase::BeginPlay()
{
	
}