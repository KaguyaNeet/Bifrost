// Fill out your copyright notice in the Description page of Project Settings.

#include "BBTService.h"
#include "BAIController.h"
#include "BCharacterBase.h"
#include "BUnitManager.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ABAIController* aiController = Cast<ABAIController>(OwnerComp.GetAIOwner());
	ABCharacterBase* character = Cast<ABCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	UBlackboardComponent* blackboard = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	if (nullptr != aiController && nullptr != character && nullptr != blackboard)
	{
		RecieveTickAI(aiController, character, blackboard, DeltaSeconds);
	}
}

void UBBTService::RecieveTickAI(ABAIController * controller, ABCharacterBase * character, UBlackboardComponent* blackboard, float DeltaTime)
{
	EAIState& aiState = controller->m_AIState;
	if (EAIState::ENone == aiState)
	{
		aiState = EAIState::EPatrol;
		return;
	}
	else if (EAIState::EPatrol == aiState || EAIState::EMove == aiState)
	{
		ABUnitManager* unitManager = ABUnitManager::GetUnitManager(controller);
		ABUnit* enemy = unitManager->GetNearestEnemy(character);
		if (nullptr == enemy)
		{
			aiState = EAIState::EPatrol;
			return;
		}
		float distance = FVector::Distance(enemy->GetActorLocation(), character->GetActorLocation());
		if (distance <= character->m_SearchDistance)
		{
			blackboard->SetValueAsObject(FName(TEXT("Enemy")), enemy);
			aiState = (distance <= character->m_AttackDistance ? EAIState::EAttack : EAIState::EMove);
		}
		else
		{
			aiState = EAIState::EPatrol;
		}
	}
	else if (EAIState::EAttack == aiState)
	{
		if (ABUnit* enemy = Cast<ABUnit>(blackboard->GetValueAsObject(FName(TEXT("Enemy")))))
		{
			if (EUnitLifeState::EDeath == enemy->m_UnitState)
			{
				aiState = EAIState::EPatrol;
				return;
			}
			float distance = FVector::Distance(enemy->GetActorLocation(), character->GetActorLocation());
			if (distance > character->m_AttackDistance)
			{
				aiState = EAIState::EMove;
			}
		}
		else
		{
			aiState = EAIState::EPatrol;
		}
	}
}
