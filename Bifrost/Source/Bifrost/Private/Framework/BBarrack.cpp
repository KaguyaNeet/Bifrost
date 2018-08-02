// Fill out your copyright notice in the Description page of Project Settings.

#include "BBarrack.h"
#include "BCharacterBase.h"
#include "BPlayerController.h"
#include "BGameInstance.h"

#include "Classes/Components/ArrowComponent.h"
#include "Classes/Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ABBarrack::ABBarrack()
{
	m_SpawnArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnArrowComponent"));
}

void ABBarrack::StartProduce()
{
	UE_LOG(LogTemp, Warning, TEXT("ClickStartProduce"));
	if (EBuildingState::EStop == m_State)
	{
		if (ABPlayerController* playerController = ABPlayerController::GetPlayerController(this))
		{
			
			if (playerController->CostMoney(m_CurrentCost))
			{
				m_LastCost = m_CurrentCost;
				Super::StartProduce();
			}
			else
			{
				m_State = EBuildingState::EBlock;
				GetWorldTimerManager().SetTimer(m_CheckProduceTimer, this, &ABBarrack::StartProduce, false, 1.f);
			}
		}
		else
		{
			m_State = EBuildingState::EStop;
		}
	}
}

void ABBarrack::StopProduce()
{
	if (EBuildingState::EProduce == m_State)
	{
		Super::StopProduce();

		if (ABPlayerController* playerController = ABPlayerController::GetPlayerController(this))
		{
			playerController->AddMoney(m_LastCost);
		}
	}
}

UINT16 ABBarrack::CalculateCurrentCardCost()
{
	UINT16 result = 0;
	for (auto it : m_Cards)
	{
		if (ECardType::EBuilding != it->m_CardAttribute.m_CardType && it->m_Active)
		{
			result += it->m_CardAttribute.m_ProduceCardCost;
		}
	}
	return result;
}

void ABBarrack::Produce()
{
	if (ROLE_Authority == Role)
	{
		if (UWorld* world = GetWorld())
		{
			FActorSpawnParameters spawnParam;
			spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			ABCharacterBase* character = world->SpawnActor<ABCharacterBase>(m_CharacterClass, m_SpawnArrowComponent->GetComponentLocation(), m_SpawnArrowComponent->GetComponentRotation(), spawnParam);
			Test(character);
		}
	}
	StartProduce();
}

void ABBarrack::BeginPlay()
{
	Super::BeginPlay();

	if (nullptr != m_LevelInfoTable)
	{
		TArray<FBarrackLevelInfoBP*> barrackInfo;
		m_LevelInfoTable->GetAllRows(TEXT(""), barrackInfo);
		for (auto it : barrackInfo)
		{
			m_BaseLevelInfo.Add(it->BaseInfo);
			m_BarrackInfo.Add(it->BarrackInfo);
		}
	}
}

void ABBarrack::Update()
{
	Super::Update();
}
