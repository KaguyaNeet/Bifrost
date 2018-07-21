// Fill out your copyright notice in the Description page of Project Settings.

#include "BBuildingBase.h"

#include "Classes/GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

ABBuildingBase::ABBuildingBase()
{
	GetMovementComponent()->SetActive(false);
}

//Only called on serve
void ABBuildingBase::StartProduce()
{
	GetWorldTimerManager().SetTimer(m_ProduceTimer, this, &ABBuildingBase::Produce, m_MaxProduceTime, true, m_MaxProduceTime);
}

void ABBuildingBase::Produce()
{
}

void ABBuildingBase::BeginPlay()
{
	Super::BeginPlay();

	StartProduce();
}
