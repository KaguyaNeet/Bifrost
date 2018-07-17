// Fill out your copyright notice in the Description page of Project Settings.

#include "BGameInstance.h"
#include "BUnitManager.h"
#include "BBuffManager.h"


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