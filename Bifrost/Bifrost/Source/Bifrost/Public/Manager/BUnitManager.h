// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BUnitManager.generated.h"

UCLASS()
class BIFROST_API ABUnitManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABUnitManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddUnit(class ABUnit*);
	void RemoveUnit(class ABUnit*);

	static ABUnitManager* GetUnitManager(AActor* caller);

	class ABUnit* GetNearestFriend(class ABUnit* caller);
	class ABUnit* GetNearestEnemy(class ABUnit* caller);
	TArray<class ABUnit*> GetInRangeFriendsNotIncludeSelf(class ABUnit* caller, float range);
	TArray<class ABUnit*> GetInRangeEnemies(class ABUnit* caller, float range);

	TArray<class ABUnit*> GetInRangeUnitsNotIncludeSelf(class ABUnit* caller, float range);
	TArray<class ABCharacter*> GetInRangeCharactersNoIncludeSelf(class ABCharacter* caller, float range);

private:
	float buffTickCounter = 0;

	UPROPERTY()
		TArray<class ABUnit*> unitList;
	UPROPERTY()
		TArray<class ABUnit*> redUnitList;
	UPROPERTY()
		TArray<class ABUnit*> blueUnitList;

private:

	/*
	* Get the nearest unit of caller.
	* @param caller. caller's ptr.
	* @param list. find unit in this list.
	* @param ATOWBaseUnit*. return the found unit, can be nullptr.
	**/
	class ABUnit* GetNearestUnit(class ABUnit* caller, const TArray<class ABUnit*>& list);

	/*
	* Get the units in caller's range, not include caller self.
	* @param caller. caller's ptr.
	* @param range. find in this range.
	* @param list. find unit in this list.
	* @param TArray<ATOWBaseUnit*>. return the found units, can be null array.
	**/
	template<typename T>
	TArray<T*> GetInRangeUnitsNotIncludeSelf(T* caller, float range, const TArray<T*>& list);

	/*
	* Get two actors distance.
	**/
	float Distance(AActor* a, AActor* b);
	
};
