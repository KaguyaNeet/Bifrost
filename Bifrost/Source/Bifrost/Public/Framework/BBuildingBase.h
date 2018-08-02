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
	EBlock UMETA(DisplayName = "Block"),
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
		UINT8 UpdateTime = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelInfo")
		int CostMoney = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelInfo")
		float ProduceTime = 5.f;
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
	
	UFUNCTION(BlueprintCallable)
		virtual void StartUpdate();
	UFUNCTION(BlueprintCallable)
		virtual void StopUpdate();
	UFUNCTION(BlueprintCallable)
		virtual void StartProduce();
	UFUNCTION(BlueprintCallable)
		virtual void StopProduce();

	UFUNCTION(BlueprintCallable)
		void AddCard(UBCard* card);

protected:
	virtual void BeginPlay() override;

	virtual void Produce();
	virtual void Update();

	inline int GetLevelInArray()
	{
		return FMath::Clamp((int)(m_Level - 1), 0, m_BaseLevelInfo.Num() - 1);
	}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProduceProperty")
		float m_MaxProduceTime = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProduceProperty")
		UDataTable* m_LevelInfoTable = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UINT8 m_Level = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EBuildingState m_State = EBuildingState::EStop;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<FBuildingBaseLevelInfo> m_BaseLevelInfo;
private:
	FTimerHandle m_ProduceTimer;
	FTimerHandle m_UpdateTimer;
};
