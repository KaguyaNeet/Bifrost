#include "BUnit.h"
#include "BUnitManager.h"


ABUnit::ABUnit()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABUnit::BeginPlay()
{
	Super::BeginPlay();
	
	if (ROLE_Authority == Role)
	{
		ABUnitManager* unitManager = ABUnitManager::GetUnitManager(this);
		unitManager->AddUnit(this);
	}
}

void ABUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_UnitTickCounter += DeltaTime;
	m_UnitTickCounter >= 1.f ? UnitTick(), m_UnitTickCounter = 0.f : false;
}

void ABUnit::ApplyDamage(const FDamageAttribute& damageAttribute, ABUnit * damageCauser)
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

	ChangeLifeValue(-actualDamage);
}

bool ABUnit::ChangeLifeValue(INT32 value)
{
	m_BaseAttribute.currentLifeValue = FMath::Clamp(m_BaseAttribute.currentLifeValue + value, 0, (int)m_BaseAttribute.maxLifeValue);
	return m_BaseAttribute.currentLifeValue == 0 ? false : true;
}

void ABUnit::Death(ABUnit * damageCauser)
{
	m_UnitState = EUnitLifeState::EDeath;
	if (ABUnitManager* unitManager = ABUnitManager::GetUnitManager(this))
	{
		unitManager->RemoveUnit(this);
	}
}

void ABUnit::UnitTick()
{

}

