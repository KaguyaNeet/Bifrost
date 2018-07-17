// Fill out your copyright notice in the Description page of Project Settings.

#include "BBuff.h"
#include "BUnit.h"

void UBBuff::Initialize(class ABUnit* owner, ABUnit * adder, EBuffType buffType, int lifetime, int buffKey, AddBuffFunction addFunc, TickBuffFunction tickFunc, RemoveBuffFunction removeFunc)
{
	m_BuffAdder = adder;
	m_BuffType = buffType;
	m_LifeTime = lifetime;
	m_Key = buffKey;
	m_AddBuffFunction = addFunc;
	m_TickBuffFunction = tickFunc;
	m_RemoveBuffFunction = removeFunc;

	owner->m_BuffList.Add(this);
	AddBuff(owner);
}

void UBBuff::AddBuff(ABUnit* owner)
{
	if (nullptr != m_AddBuffFunction)
	{
		m_AddBuffFunction(owner, m_BuffAdder);
	}
}

void UBBuff::TickBuff(ABUnit* owner)
{
	//Run buff tick function here.
	if (nullptr != m_TickBuffFunction)
	{
		m_TickBuffFunction(owner, m_BuffAdder);
	}

	if (EBuffType::ELifetime == m_BuffType)
	{
		m_LifeTime--;
		if (m_LifeTime <= 0)
		{
			RemoveBuff(owner);
		}
	}
}

void UBBuff::RemoveBuff(ABUnit* owner)
{
	//Run remove function here.
	if (nullptr != m_RemoveBuffFunction)
	{
		m_RemoveBuffFunction(owner, m_BuffAdder);
	}

	owner->m_BuffList.Remove(this);
	owner->m_ShieldMap.Remove(this);
}


