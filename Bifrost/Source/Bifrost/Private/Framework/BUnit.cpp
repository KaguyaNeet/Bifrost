// Fill out your copyright notice in the Description page of Project Settings.

#include "BUnit.h"
#include "BUnitManager.h"
#include "BBuff.h"

// Sets default values
ABUnit::ABUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABUnit::BeginPlay()
{
	Super::BeginPlay();
	
	if (ROLE_Authority == Role)
	{
		if (ABUnitManager* unitManager = ABUnitManager::GetUnitManager(this))
		{
			unitManager->AddUnit(this);
		}
	}
}

bool ABUnit::ChangeLifeValue(INT32 value)
{
	m_BaseAttribute.currentLifeValue = FMath::Clamp(m_BaseAttribute.currentLifeValue + value, 0, (int)m_BaseAttribute.maxLifeValue);
	return m_BaseAttribute.currentLifeValue == 0 ? false : true;
}

void ABUnit::Death(ABUnit * deathCauser)
{
	m_UnitState = EUnitLifeState::EDeath;
	if (ABUnitManager* unitManager = ABUnitManager::GetUnitManager(this))
	{
		unitManager->RemoveUnit(this);
	}
}

void ABUnit::UnitTick()
{
	for (auto it : m_BuffList)
	{
		it->TickBuff(this);
	}
}

// Called every frame
void ABUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_UnitTickCounter += DeltaTime;
	m_UnitTickCounter >= UNIT_TICK_TIME ? UnitTick(), m_UnitTickCounter = 0.f : false;
}

void ABUnit::ApplyDamage(const FDamageAttribute & damageAttribute, ABUnit * damageCauser)
{
	if (m_UnitState == EUnitLifeState::EDeath || m_UnitBuffState[(UINT8)EUnitBuffState::Invincible])
		return;

	INT32 actualDamage = 0;
	if (EDamageType::True == damageAttribute.damageType)
	{
		actualDamage = damageAttribute.damageValue;
	}
	else
	{
		UINT8 originalDefense = EDamageType::Physical == damageAttribute.damageType ? m_BaseAttribute.physicalDefense : m_BaseAttribute.magicDefense;
		UINT8 actualDefense = originalDefense * (1 - static_cast<float>(damageAttribute.penetration) / MAX_DEFENSE);
		actualDamage = damageAttribute.damageValue * (1 - static_cast<float>(actualDefense) / MAX_DEFENSE);
	}
	
	TArray<UBBuff*> shieldBuffs;
	m_ShieldMap.GetKeys(shieldBuffs);

	for (int i = 0; i < shieldBuffs.Num(); i++)
	{
		int& shieldValue = *m_ShieldMap.Find(shieldBuffs[i]);
		if (shieldValue <= actualDamage)
		{
			actualDamage -= shieldValue;
			shieldValue = 0;
			shieldBuffs[i]->RemoveBuff(this);
		}
		else
		{
			shieldValue -= actualDamage;
			actualDamage = 0;
			break;
		}
	}

	if (!ChangeLifeValue(-actualDamage))
	{
		Death(damageCauser);
	}
	
}

void ABUnit::Initialize()
{
}
