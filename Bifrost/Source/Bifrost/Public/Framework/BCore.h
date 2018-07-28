// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/BBuildingBase.h"
#include "BCore.generated.h"

USTRUCT()
struct FCoreLevelInfo : public FTableRowBase
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
class BIFROST_API ABCore : public ABBuildingBase
{
	GENERATED_BODY()
	
public:
	ABCore();

	static ABCore* GetEnemyCore(EUnitCamp selfCamp, AActor* caller);

protected:
	virtual void BeginPlay() override;
	
	
};
