// Fill out your copyright notice in the Description page of Project Settings.

#include "BBuildingBase.h"
#include "BGameInstance.h"
#include "BPlayerController.h"

#include "Classes/GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

ABBuildingBase::ABBuildingBase()
{
	GetMovementComponent()->SetActive(false);
}

//Only called on serve
void ABBuildingBase::StartProduce()
{
	m_State = EBuildingState::EProduce;
	GetWorldTimerManager().SetTimer(m_ProduceTimer, this, &ABBuildingBase::Produce, m_MaxProduceTime, true, m_MaxProduceTime);
	GetWorldTimerManager().ClearTimer(m_ProduceTimer);
}

void ABBuildingBase::Produce()
{
}

void ABBuildingBase::BeginPlay()
{
	Super::BeginPlay();

	m_Level = 0;
	UpdateInfo();

}

void ABBuildingBase::StartUpdate()
{
	if (ABPlayerController* playerController = ABPlayerController::GetPlayerController(this))
	{
		if (playerController->CostMoney(m_BaseLevelInfo.CostMoney))
		{
			m_State = EBuildingState::EUpdate;
			GetWorldTimerManager().SetTimer(m_UpdateTimer, this, &ABBuildingBase::UpdateInfo, false, m_BaseLevelInfo.UpdateTime);
			GetWorldTimerManager().ClearTimer(m_ProduceTimer);
		}
	}
}

void ABBuildingBase::UpdateInfo()
{
	m_Level++;

	StartProduce();
}

void ABBuildingBase::StopUpdate()
{
	if (EBuildingState::EUpdate == m_State)
	{
		m_State = EBuildingState::EProduce;
		GetWorldTimerManager().ClearTimer(m_UpdateTimer);
		StartProduce();

		if (ABPlayerController* playerController = ABPlayerController::GetPlayerController(this))
		{
			playerController->AddMoney(m_BaseLevelInfo.CostMoney);
		}
	}
}
