// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BUnit.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BIFROST_API ABPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ABPlayerController();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

	bool CostMoney(UINT16 costValue);
	void AddMoney(UINT16 value);
	UINT32 GetMoney();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
		EUnitCamp m_PlayerCamp = EUnitCamp::ENeatual;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
		int m_Money = 0;
	static ABPlayerController* GetPlayerController(ABUnit* caller);
private:
	
};
