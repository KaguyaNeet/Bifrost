// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"

#include "CoreMinimal.h"
#include "Framework/BUnit.h"
#include "BBuildingBase.generated.h"

UENUM(BlueprintType)
enum class EBuildingState: uint8
{
	EConstruction UMETA(DisplayName = "Construction"),
	EUpdate UMETA(DisplayName = "Update"),
	EProduce UMETA(DisplayName = "Produce"),
	EStop UMETA(DisplayName = "Stop"),
	EDestroy UMETA(DisplayName = "Destroy")
};

USTRUCT()
struct FBuildingBaseLevelInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelInfo")
		UINT8 Level = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelInfo")
		UINT8 UpdateTime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelInfo")
		int CostMoney = 0;
};

/**
 * 
 */
UCLASS()
class BIFROST_API ABBuildingBase : public ABUnit
{
	GENERATED_BODY()
	
public:
	ABBuildingBase();
	
	void StartProduce();

	virtual void Produce();

protected:
	virtual void BeginPlay() override;

	virtual void StartUpdate();
	virtual void UpdateInfo();
	virtual void StopUpdate();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProduceProperty")
		float m_MaxProduceTime = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProduceProperty")
		UDataTable* m_LevelInfoTable = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UINT8 m_Level = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EBuildingState m_State = EBuildingState::EConstruction;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FBuildingBaseLevelInfo m_BaseLevelInfo;
private:
	FTimerHandle m_ProduceTimer;
	FTimerHandle m_UpdateTimer;
};
