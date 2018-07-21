// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/BBuildingBase.h"
#include "BBarrack.generated.h"

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
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		class UArrowComponent* m_SpawnArrowComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProduceProperty")
		UClass* m_CharacterClass;
	
};
