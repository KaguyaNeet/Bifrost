// Fill out your copyright notice in the Description page of Project Settings.

#include "BCore.h"
#include "BGameInstance.h"

ABCore::ABCore()
{

}

ABCore * ABCore::GetEnemyCore(EUnitCamp selfCamp, AActor* caller)
{
	if (ROLE_Authority == caller->Role)
	{
		if (UBGameInstance* gameInstance = Cast<UBGameInstance>(caller->GetGameInstance()))
		{
			return gameInstance->GetEnemyCore(selfCamp);
		}
	}
	return nullptr;
}

void ABCore::BeginPlay()
{
	Super::BeginPlay();
	
	if (ROLE_Authority == Role)
	{
		if (UBGameInstance* gameInstance = Cast<UBGameInstance>(GetGameInstance()))
		{
			gameInstance->SetCore(this);
		}
	}
}
