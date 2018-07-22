// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BIFROST_API ABGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameProperty")
		float m_BodyStrengthLifeAddtion = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameProperty")
		float m_BodyStrengthPhysicalAddtion = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameProperty")
		float m_BodyStrengthMagicAddtion = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameProperty")
		float m_IntelligenceDamageAddtion = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameProperty")
		float m_IntelligenceDefenseAddtion = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameProperty")
		float m_IntelligencePenetrationAddtion = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameProperty")
		float m_PowerDamageAddtion = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameProperty")
		float m_PowerDefenseAddtion = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameProperty")
		float m_PowerPenetrationAddtion = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameProperty")
		float m_AgileAttackSpeedAddtion = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameProperty")
		float m_AgileMoveSpeedAddtion = 0;

};
