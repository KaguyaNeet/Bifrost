// Fill out your copyright notice in the Description page of Project Settings.

#include "BAIController.h"
#include "BCharacterBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ABAIController::ABAIController()
{
	m_BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	m_BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void ABAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	ABCharacterBase* Unit = Cast<ABCharacterBase>(InPawn);
	if (Unit && Unit->m_BehaviorTree && Unit->m_BehaviorTree->BlackboardAsset)
	{
		m_BlackboardComponent->InitializeBlackboard(*Unit->m_BehaviorTree->BlackboardAsset);
		Blackboard = m_BlackboardComponent;
		m_BehaviorTreeComponent->StartTree(*Unit->m_BehaviorTree);
	}
}

void ABAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ABAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
