// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BAIController.generated.h"

/**
 * 
 */
UCLASS()
class BIFROST_API ABAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere)
		class UBehaviorTreeComponent* m_BehaviorTreeComponent;
	UPROPERTY(EditAnywhere)
		class UBlackboardComponent* m_BlackboardComponent;

public:
	ABAIController();
	
	virtual void Possess(APawn* InPawn) override;

	virtual void BeginPlay() override;

protected:
	virtual void Tick(float DeltaTime) override;
};
