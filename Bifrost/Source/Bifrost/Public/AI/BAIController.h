// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BAIController.generated.h"

UENUM(BlueprintType)
enum class EAIState : uint8
{
	ENone UMETA(DisplayName = "None"),
	EPatrol UMETA(DisplayName = "Patrol"),
	EMove UMETA(DisplayName = "Move"),
	EAttack UMETA(DisplayName = "Attack"),
};

/**
 * 
 */
UCLASS()
class BIFROST_API ABAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		class UBehaviorTreeComponent* m_BehaviorTreeComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
		class UBlackboardComponent* m_BlackboardComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIState")
		EAIState m_AIState = EAIState::ENone;
public:
	ABAIController();
	
	virtual void Possess(APawn* InPawn) override;

	virtual void BeginPlay() override;

protected:
	virtual void Tick(float DeltaTime) override;
};
