// Fill out your copyright notice in the Description page of Project Settings.

#include "BBarrack.h"
#include "BCharacterBase.h"
#include "BPlayerController.h"
#include "BGameInstance.h"

#include "Classes/Components/ArrowComponent.h"
#include "Classes/Engine/World.h"
#include "Kismet/GameplayStatics.h"

ABBarrack::ABBarrack()
{
	m_SpawnArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnArrowComponent"));
}

void ABBarrack::Produce()
{
	if (ROLE_Authority == Role)
	{
		if (ABPlayerController* playerController = ABPlayerController::GetPlayerController(this))
		{
			if (playerController->CostMoney(m_CurrentCost))
			{
				if (UWorld* world = GetWorld())
				{
					FActorSpawnParameters spawnParam;
					spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
					ABCharacterBase* character = world->SpawnActor<ABCharacterBase>(m_CharacterClass, m_SpawnArrowComponent->GetComponentLocation(), m_SpawnArrowComponent->GetComponentRotation(), spawnParam);
					Test(character);

				}
			}
			else
			{
				//Print no money here.
			}
		}
	}
}

void ABBarrack::BeginPlay()
{
	Super::BeginPlay();


}

void ABBarrack::UpdateInfo()
{
	Super::UpdateInfo();
}
