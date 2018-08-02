// Fill out your copyright notice in the Description page of Project Settings.

#include "BGameInstance.h"
#include "BUnitManager.h"
#include "BBuffManager.h"
#include "BCore.h"
#include "BPlayerController.h"

#include "Kismet/GameplayStatics.h"

ABUnitManager* UBGameInstance::GetUnitManager()
{
	if (nullptr == m_UnitManager)
	{
		if (UWorld* world = GetWorld())
		{
			ABUnitManager* unitManager = world->SpawnActor<ABUnitManager>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
			m_UnitManager = unitManager;
		}
		else
		{
			return nullptr;
		}
	}
	return m_UnitManager;
}

ABBuffManager* UBGameInstance::GetBuffManager()
{
	if (nullptr == m_BuffManager)
	{
		if (UWorld* world = GetWorld())
		{
			ABBuffManager* buffManager = world->SpawnActor<ABBuffManager>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
			m_BuffManager = buffManager;
		}
		else
		{
			return nullptr;
		}
	}
	return m_BuffManager;
}

ABCore * UBGameInstance::GetEnemyCore(EUnitCamp selfCamp)
{
	if (EUnitCamp::ENeatual == selfCamp)
	{
		return nullptr;
	}
	
	if (nullptr == m_RedCore || nullptr == m_BlueCore)
	{
		TArray<AActor*> coreLists;
		UGameplayStatics::GetAllActorsOfClass(this, ABCore::StaticClass(), coreLists);
		for (auto it : coreLists)
		{
			if (ABCore* core = Cast<ABCore>(it))
			{
				core->m_UnitCamp == EUnitCamp::EBlue ? m_BlueCore = core : m_RedCore = core;
			}
			else
			{
				return nullptr;
			}
		}
	}
	return (selfCamp == EUnitCamp::EBlue ? m_RedCore : m_BlueCore);
}

void UBGameInstance::SetCore(ABCore * core)
{
	if (EUnitCamp::ENeatual == core->m_UnitCamp)
	{
		return;
	}
	core->m_UnitCamp == EUnitCamp::EBlue ? m_BlueCore = core : m_RedCore = core;
}

void UBGameInstance::SetPlayerController(ABPlayerController * playerController)
{
	if (nullptr != playerController)
	{
		if (nullptr == m_RedPlayerController)
		{
			m_RedPlayerController = playerController;
			return;
		}
		if (nullptr == m_BluePlayerController)
		{
			m_BluePlayerController = playerController;
			return;
		}
	}
}

ABPlayerController * UBGameInstance::GetPlayerController(EUnitCamp camp)
{
	return (EUnitCamp::ERed == camp ? m_RedPlayerController : m_BluePlayerController);
}
