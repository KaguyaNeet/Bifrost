// Fill out your copyright notice in the Description page of Project Settings.

#include "BUnitManager.h"
#include "Bunit.h"
#include "BCharacter.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ABUnitManager::ABUnitManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABUnitManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABUnitManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABUnitManager::AddUnit(ABUnit* unit)
{
	if (unit)
	{
		unitList.Add(unit);
		EUnitCamp::ERed == unit->m_UnitCamp ? redUnitList.Add(unit) : blueUnitList.Add(unit);
	}
}

void ABUnitManager::RemoveUnit(ABUnit* unit)
{
	if (unit)
	{
		unitList.Remove(unit);
		EUnitCamp::ERed == unit->m_UnitCamp ? redUnitList.Remove(unit) : blueUnitList.Remove(unit);
	}
}

ABUnitManager* ABUnitManager::GetUnitManager(AActor* caller)
{
	TArray<AActor*> outManager;
	UGameplayStatics::GetAllActorsOfClass(caller, ABUnitManager::StaticClass(), outManager);
	if (outManager.Num() > 0 && outManager[0])
	{
		return Cast<ABUnitManager>(outManager[0]);
	}
	else
	{
		return caller->GetWorld()->SpawnActor<ABUnitManager>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	}
}

float ABUnitManager::Distance(AActor* a, AActor* b)
{
	return FVector::Distance(a->GetActorLocation(), a->GetActorLocation());
}

ABUnit* ABUnitManager::GetNearestUnit(class ABUnit* caller, const TArray<ABUnit*>& list)
{
	float tempNearest = FLT_MAX;
	ABUnit* tempNearestUnit = nullptr;
	for (auto it : list)
	{
		if (it != caller)
		{
			float temp = Distance(it, caller);
			temp < tempNearest ? tempNearest = temp, tempNearestUnit = it: false;
		}
	}
	return tempNearestUnit;
}

template<typename T>
TArray<T*> ABUnitManager::GetInRangeUnitsNotIncludeSelf(T* caller, float range, const TArray<T*>& list)
{
	TArray<T*> tempArray;
	for (auto it : list)
	{
		if (it != caller)
		{
			float temp = Distance(it, caller);
			temp <= range ? tempArray.Add(it) : false;
		}
	}
	return tempArray;
}

ABUnit* ABUnitManager::GetNearestFriend(ABUnit* caller)
{
	return GetNearestUnit(caller, EUnitCamp::ERed == caller->m_UnitCamp ? redUnitList : blueUnitList);
}

ABUnit* ABUnitManager::GetNearestEnemy(ABUnit* caller)
{
	return GetNearestUnit(caller, EUnitCamp::ERed == caller->m_UnitCamp ? blueUnitList : redUnitList);
}

TArray<ABUnit*> ABUnitManager::GetInRangeFriendsNotIncludeSelf(ABUnit* caller, float range)
{
	return GetInRangeUnitsNotIncludeSelf(caller, range, EUnitCamp::ERed == caller->m_UnitCamp ? redUnitList : blueUnitList);
}

TArray<ABUnit*> ABUnitManager::GetInRangeEnemies(ABUnit* caller, float range)
{
	return GetInRangeUnitsNotIncludeSelf(caller, range, EUnitCamp::ERed == caller->m_UnitCamp ? blueUnitList : redUnitList);
}

TArray<ABUnit*> ABUnitManager::GetInRangeUnitsNotIncludeSelf(ABUnit* caller, float range)
{
	return GetInRangeUnitsNotIncludeSelf(caller, range, unitList);
}

TArray<class ABCharacter*> ABUnitManager::GetInRangeCharactersNoIncludeSelf(ABCharacter * caller, float range)
{
	TArray<ABCharacter*> characterList;
	for (auto it : unitList)
	{
		if (ABCharacter* character = Cast<ABCharacter>(it))
		{
			characterList.Add(character);
		}
	}
	return GetInRangeUnitsNotIncludeSelf<ABCharacter>(caller, range, characterList);
}
