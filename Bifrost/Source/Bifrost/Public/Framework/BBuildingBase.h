// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/BUnit.h"
#include "BBuildingBase.generated.h"

/**
 * 
 */
UCLASS()
class BIFROST_API ABBuildingBase : public ABUnit
{
	GENERATED_BODY()
	
public:
	ABBuildingBase();
	
	void StartProduce();

	virtual void Produce();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProduceProperty")
		float m_MaxProduceTime = 0.f;

private:
	FTimerHandle m_ProduceTimer;
};
