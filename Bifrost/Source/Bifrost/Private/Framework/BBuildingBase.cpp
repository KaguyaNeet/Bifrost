// Fill out your copyright notice in the Description page of Project Settings.

#include "BBuildingBase.h"

#include "Classes/GameFramework/CharacterMovementComponent.h"

ABBuildingBase::ABBuildingBase()
{
	GetMovementComponent()->SetActive(false);
}


