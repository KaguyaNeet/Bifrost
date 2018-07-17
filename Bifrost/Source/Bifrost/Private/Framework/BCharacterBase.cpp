// Fill out your copyright notice in the Description page of Project Settings.

#include "BCharacterBase.h"
#include "BAIController.h"

#include "GameFramework/CharacterMovementComponent.h"

ABCharacterBase::ABCharacterBase()
{
	AIControllerClass = ABAIController::StaticClass();

	GetCharacterMovement()->bUseRVOAvoidance = true;
}

void ABCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
