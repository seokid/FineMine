// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameInfo.h"
#include "AssetManager/AssetPathMain.h"
#include "GameFramework/GameModeBase.h"
#include "FindMineGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FINDMINE_API AFindMineGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFindMineGameModeBase();

protected:
	UAssetPathMain* m_MainAssetPath;
protected:
	virtual void BeginPlay() override;
};
