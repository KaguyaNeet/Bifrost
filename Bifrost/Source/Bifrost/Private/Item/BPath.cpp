// Fill out your copyright notice in the Description page of Project Settings.

#include "BPath.h"
#include "Classes/Components/SplineComponent.h"


// Sets default values
ABPath::ABPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_Path = CreateDefaultSubobject<USplineComponent>(TEXT("path"));
}
