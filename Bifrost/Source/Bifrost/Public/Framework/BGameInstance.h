// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BUnit.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BIFROST_API UBGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	class ABUnitManager* GetUnitManager();
	class ABBuffManager* GetBuffManager();
	class ABCore* GetEnemyCore(EUnitCamp selfCamp);
	void SetCore(class ABCore* core);
	void SetPlayerController(class ABPlayerController* playerController);
	class ABPlayerController* GetPlayerController(EUnitCamp camp);
private:
	class ABUnitManager* m_UnitManager = nullptr;
	class ABBuffManager* m_BuffManager = nullptr;
	class ABCore* m_RedCore = nullptr;
	class ABCore* m_BlueCore = nullptr;

	class ABPlayerController* m_RedPlayerController = nullptr;
	class ABPlayerController* m_BluePlayerController = nullptr;
};
