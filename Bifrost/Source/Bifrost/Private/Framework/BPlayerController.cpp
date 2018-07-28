// Fill out your copyright notice in the Description page of Project Settings.

#include "BPlayerController.h"
#include "BGameInstance.h"

#include "Public/Net/UnrealNetwork.h"

ABPlayerController::ABPlayerController()
{

}

void ABPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABPlayerController, m_Money);

}

bool ABPlayerController::CostMoney(UINT16 costValue)
{
	if (ROLE_Authority == Role)
	{
		if (m_Money >= costValue)
		{
			m_Money -= costValue;
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void ABPlayerController::AddMoney(UINT16 value)
{
	m_Money += value;
}

UINT32 ABPlayerController::GetMoney()
{
	return m_Money;
}

ABPlayerController * ABPlayerController::GetPlayerController(ABUnit * caller)
{
	if (UBGameInstance* gameInstance = Cast<UBGameInstance>(caller->GetGameInstance()))
	{
		return gameInstance->GetPlayerController(caller->m_UnitCamp);
	}
	else
	{
		return nullptr;
	}
}

