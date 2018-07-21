// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BBTService.generated.h"

/**
 * 
 */
UCLASS()
class BIFROST_API UBBTService : public UBTService
{
	GENERATED_BODY()
	
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	void RecieveTickAI(class ABAIController* controller, class ABCharacterBase* character, class UBlackboardComponent* blackboard, float DeltaTime);
};
