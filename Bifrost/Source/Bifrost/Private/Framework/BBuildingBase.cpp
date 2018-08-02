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
}

void ABBuildingBase::StopProduce()
{
	m_State = EBuildingState::EStop;
	GetWorldTimerManager().ClearTimer(m_ProduceTimer);
}

void ABBuildingBase::AddCard(UBCard * card)
{
}


void ABBuildingBase::Produce()
{
	StartProduce();
}

void ABBuildingBase::BeginPlay()
{
	Super::BeginPlay();

	m_Level = 1;
}

void ABBuildingBase::StartUpdate()
{
	UE_LOG(LogTemp, Warning, TEXT("ClickStartUpdate"));
	if (ABPlayerController* playerController = ABPlayerController::GetPlayerController(this))
	{
		if (m_Level < m_BaseLevelInfo.Num() && playerController->CostMoney(m_BaseLevelInfo[GetLevelInArray()].CostMoney))
		{
			StopProduce();
			m_State = EBuildingState::EUpdate;
			GetWorldTimerManager().SetTimer(m_UpdateTimer, this, &ABBuildingBase::Update, false, m_BaseLevelInfo[GetLevelInArray()].UpdateTime);
		}
	}
}

void ABBuildingBase::StopUpdate()
{
	if (EBuildingState::EUpdate == m_State)
	{
		m_State = EBuildingState::EStop;
		GetWorldTimerManager().ClearTimer(m_UpdateTimer);
		StartProduce();

		if (ABPlayerController* playerController = ABPlayerController::GetPlayerController(this))
		{
			playerController->AddMoney(m_BaseLevelInfo[GetLevelInArray()].CostMoney);
		}
	}
}


void ABBuildingBase::Update()
{
	m_Level++;
	m_State = EBuildingState::EStop;
	StartProduce();
}

