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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBehaviorTree* m_BehaviorTree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterProperty")
		float m_SearchDistance = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterProperty")
		float m_AttackDistance = 0.f;
	
	
};
