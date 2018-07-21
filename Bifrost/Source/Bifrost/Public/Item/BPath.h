// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BUnit.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BPath.generated.h"

UCLASS()
class BIFROST_API ABPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABPath();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
		class USplineComponent* m_Path;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		EUnitCamp m_PathCamp = EUnitCamp::ENeatual;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		bool m_IsUpPath = true;
};
