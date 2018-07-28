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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelInfo")
		FBuildingBaseLevelInfo BaseInfo;

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

private:
	virtual void UpdateInfo() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		class UArrowComponent* m_SpawnArrowComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProduceProperty")
		UClass* m_CharacterClass;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int m_CurrentCost = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FBarrackLevelInfo m_CurrentInfo;
};
