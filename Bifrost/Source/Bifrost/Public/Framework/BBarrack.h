// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/BBuildingBase.h"
#include "BBarrack.generated.h"

USTRUCT()
struct FBarrackLevelInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

};

USTRUCT()
struct FBarrackLevelInfoBP : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelInfo")
		FBuildingBaseLevelInfo BaseInfo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelInfo")
		FBarrackLevelInfo BarrackInfo;

};

/**
 * 
 */
UCLASS()
class BIFROST_API ABBarrack : public ABBuildingBase
{
	GENERATED_BODY()
	
public:
	ABBarrack();

	virtual void Produce() override;

	UFUNCTION(BlueprintImplementableEvent)
		void Test(class ABCharacterBase* unit);

protected:
	virtual void BeginPlay() override;

	virtual void StartProduce() override;
	virtual void StopProduce() override;

	virtual UINT16 CalculateCurrentCardCost() override;

private:
	virtual void Update() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		class UArrowComponent* m_SpawnArrowComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProduceProperty")
		UClass* m_CharacterClass;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int m_CurrentCost = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<FBarrackLevelInfo> m_BarrackInfo;

private:
	UINT16 m_LastCost = 0;
	FTimerHandle m_CheckProduceTimer;
};
