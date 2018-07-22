// Fill out your copyright notice in the Description page of Project Settings.

#include "BCharacterBase.h"
#include "BAIController.h"
#include "BGameMode.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ABCharacterBase::ABCharacterBase()
{
	AIControllerClass = ABAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::Spawned;
	GetCharacterMovement()->bUseRVOAvoidance = true;
}

void ABCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABCharacterBase::SetCharacterAttributeBodyStrength(int value)
{
	m_CharacterAttribute.BodyStrength = value;
	RefreshUnitAttribute();
}

void ABCharacterBase::SetCharacterAttributeIntelligence(int value)
{
	m_CharacterAttribute.Intelligence = value;
	RefreshUnitAttribute();
}

void ABCharacterBase::SetCharacterAttributePower(int value)
{
	m_CharacterAttribute.Power = value;
	RefreshUnitAttribute();
}

void ABCharacterBase::SetCharacterAttributeAgile(int value)
{
	m_CharacterAttribute.Agile = value;
	RefreshUnitAttribute();
}

FCharacterAttribute ABCharacterBase::GetCharacterAttribute()
{
	return m_CharacterAttribute;
}

void ABCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABCharacterBase::RefreshUnitAttribute()
{
	if (ABGameMode* gameMode = Cast<ABGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		m_BaseAttribute.MaxLifeValue = m_CharacterBaseLife + m_CharacterAttribute.BodyStrength * gameMode->m_BodyStrengthLifeAddtion;

		m_BaseAttribute.PhysicalDefense = m_CharacterAttribute.BodyStrength * gameMode->m_BodyStrengthPhysicalAddtion + m_CharacterAttribute.Power * gameMode->m_PowerDefenseAddtion;
		m_BaseAttribute.MagicDefense = m_CharacterAttribute.BodyStrength * gameMode->m_BodyStrengthMagicAddtion + m_CharacterAttribute.Power * gameMode->m_IntelligenceDefenseAddtion;

		m_BaseAttribute.PhysicalDamage = m_CharacterAttribute.Power * gameMode->m_PowerDamageAddtion;
		m_BaseAttribute.MagicDamage = m_CharacterAttribute.Intelligence * gameMode->m_IntelligenceDamageAddtion;

		m_BaseAttribute.PhysicalPenetration = m_CharacterAttribute.Power * gameMode->m_PowerPenetrationAddtion;
		m_BaseAttribute.MagicPenetration = m_CharacterAttribute.Intelligence * gameMode->m_IntelligencePenetrationAddtion;

		m_BaseAttribute.AttackSpeed = FMath::Clamp((m_CharacterBaseAttackSpeed * (1 - FMath::Clamp(m_CharacterAttribute.Agile * gameMode->m_AgileAttackSpeedAddtion, 0.f, 0.999f))), 0.1f, m_CharacterBaseAttackSpeed);
	}
}
