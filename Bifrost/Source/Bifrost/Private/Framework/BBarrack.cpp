// Fill out your copyright notice in the Description page of Project Settings.

#include "BBarrack.h"
#include "BCharacterBase.h"

#include "Classes/Components/ArrowComponent.h"
#include "Classes/Engine/World.h"

ABBarrack::ABBarrack()
{
	m_SpawnArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnArrowComponent"));
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
}
