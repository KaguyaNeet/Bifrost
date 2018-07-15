// Fill out your copyright notice in the Description page of Project Settings.

#include "BCharacter.h"
#include "BUnitManager.h"

#include "Classes/Components/CapsuleComponent.h"
#include "Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Components/ArrowComponent.h"
#include "Classes/AI/Navigation/NavigationSystem.h"
#include "Classes/AI/Navigation/NavigationData.h"


ABCharacter::ABCharacter()
{
	m_pCapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	m_pCapsuleCollision->AttachTo(RootComponent);

	m_pCharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	m_pCharacterMesh->AttachTo(m_pCapsuleCollision);

	m_pForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ForwardArrow"));
	m_pForwardArrow->AttachTo(m_pCapsuleCollision);
}

void ABCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FVector::Distance(GetActorLocation(), path[currentPoint].Location) < m_MaxMoveSpeed  * DeltaTime && currentPoint < (path.Num() - 1))
		currentPoint++;
	m_MoveDirection = path[currentPoint].Location - GetActorLocation();
	m_MoveDirection.Normalize();
	if (FMath::Abs(GetActorRotation().Yaw - m_MoveDirection.Rotation().Yaw) > 10.f)
		SetActorRotation(FRotator(0.f, FMath::Lerp(GetActorRotation(), m_MoveDirection.Rotation(), 0.03f).Yaw, 0.f));
	
	RVO2(DeltaTime);
	FVector displacement = m_CurrentVelocity * DeltaTime;
	SetActorLocation(GetActorLocation() + displacement);
	m_CurrentVelocity = m_MoveDirection * m_MaxMoveSpeed;
	
	m_LastMoveDirection = m_MoveDirection;
	m_MoveDirection = FVector::ZeroVector;
}

void ABCharacter::BeginPlay()
{
	Super::BeginPlay();

	MoveTo(target);
}

void ABCharacter::MoveTo(FVector target)
{
	UNavigationSystem* navSys = GetWorld()->GetNavigationSystem();
	ANavigationData* navData = navSys->GetNavDataForProps(NavAgentProperties);
	FPathFindingQuery Query1(this, *navData, GetActorLocation(), target);
	FPathFindingResult result = navSys->FindPathSync(Query1);

	path = result.Path.Get()->GetPathPoints();
}

void ABCharacter::MoveTo(AActor * target)
{
	MoveTo(target->GetActorLocation());
}

void ABCharacter::RVO2(float DeltaTime)
{
	TArray<ABCharacter*> agentNeighbors;
	if (ABUnitManager* unitManager = ABUnitManager::GetUnitManager(this))
	{
		agentNeighbors = unitManager->GetInRangeCharactersNoIncludeSelf(this, m_MaxMoveSpeed * 2 * DeltaTime + m_pCapsuleCollision->GetScaledCapsuleRadius() * 2);
	}

	float safeDistance = 0.f;
	FVector relativeVelocity = FVector::ZeroVector;
	FVector endPosition = FVector::ZeroVector;
	ABCharacter* agent = nullptr;

	for (int i = 0; i < agentNeighbors.Num(); i++)
	{
		agent = agentNeighbors[i];
		if (nullptr == agent)
		{
			continue;
		}

		safeDistance = agent->m_pCapsuleCollision->GetScaledCapsuleRadius() + this->m_pCapsuleCollision->GetScaledCapsuleRadius();
		relativeVelocity = agent->m_CurrentVelocity - this->m_CurrentVelocity;
		endPosition = this->GetActorLocation() + relativeVelocity * DeltaTime;
		if (FVector::Distance(endPosition, agent->GetActorLocation()) < safeDistance)
		{
			//Collision
			this->m_CurrentVelocity = -m_CurrentVelocity;
		}
	}
}
