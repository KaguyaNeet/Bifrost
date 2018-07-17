// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/BUnit.h"
#include "BCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class BIFROST_API ABCharacterBase : public ABUnit
{
	GENERATED_BODY()

public:
	ABCharacterBase();

	virtual void BeginPlay() override;

protected:
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		class UBehaviorTree* m_BehaviorTree;
	
	
};
