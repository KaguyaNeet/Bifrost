// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "Framework/BUnit.h"
#include "BCharacterBase.generated.h"

USTRUCT()
struct FCharacterAttribute : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		int BodyStrength = 0;
	UPROPERTY(EditAnywhere)
		int Intelligence = 0;
	UPROPERTY(EditAnywhere)
		int Power = 0;
	UPROPERTY(EditAnywhere)
		int Agile = 0;
};
/**
 * 
 */
UCLASS()
class BIFROST_API ABCharacterBase : public ABUnit
{
	GENERATED_BODY()

public:
	ABCharacterBase();

	virtual void BeginPlay() override;

	void SetCharacterAttributeBodyStrength(int value);
	void SetCharacterAttributeIntelligence(int value);
	void SetCharacterAttributePower(int value);
	void SetCharacterAttributeAgile(int value);

	FCharacterAttribute GetCharacterAttribute();

protected:
	virtual void Tick(float DeltaTime) override;

	void RefreshUnitAttribute();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBehaviorTree* m_BehaviorTree;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterProperty")
		float m_SearchDistance = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterProperty")
		float m_AttackDistance = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterProperty")
		int m_CharacterBaseLife = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterProperty")
		float m_CharacterBaseAttackSpeed = 2.0f;

private:
		FCharacterAttribute m_CharacterAttribute;
	
};
