// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BCard.h"

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BUnit.generated.h"


enum class EDamageType
{
	Physical,
	Magic,
	True
};

enum class EUnitBuffState
{
	Invincible,
	Hurt,
	Frozen,
	Burn,
	DisableMove,
	LowSpeed,
	Dizziness,
	Silence,
	Crazy,
	max
};

UENUM(BlueprintType)
enum class EUnitCamp : uint8
{
	ERed UMETA(DisplayName = "Red"),
	EBlue UMETA(DisplayName = "Blue"),
	ENeatual UMETA(DisplayName = "Neatual")
};

UENUM(BlueprintType)
enum class EUnitLifeState: uint8
{
	EMove UMETA(DisplayName = "Move"),
	EAttack UMETA(DisplayName = "Attack"),
	EIdle UMETA(DisplayName = "Idle"),
	EDeath UMETA(DisplayName = "Death")
};

USTRUCT()
struct FUnitBaseAttribute : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		UINT16 maxLifeValue = 0;
	UPROPERTY(EditAnywhere)
		UINT16 currentLifeValue = 0;

	UPROPERTY(EditAnywhere)
		UINT8 physicalDefense = 0;
	UPROPERTY(EditAnywhere)
		UINT8 magicDefense = 0;

	UPROPERTY(EditAnywhere)
		UINT8 physicalPenetration = 0;
	UPROPERTY(EditAnywhere)
		UINT8 magicPenetration = 0;

	UPROPERTY(EditAnywhere)
		UINT16 physicalDamage = 0;
	UPROPERTY(EditAnywhere)
		UINT16 magicDamage = 0;
};

struct FDamageAttribute
{
	UINT16 damageValue = 0;
	EDamageType damageType = EDamageType::Physical;
	UINT8 penetration = 0;
};

const UINT8 MAX_DEFENSE = 100;

//How long to call UnitTick()
const float UNIT_TICK_TIME = 1.f;

UCLASS()
class BIFROST_API ABUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABUnit();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ApplyDamage(const FDamageAttribute& damageAttribute, ABUnit* damageCauser);

	virtual void Initialize();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool ChangeLifeValue(INT32 value);

	virtual void Death(ABUnit* deathCauser);

	// Called every buff circle time, not every frame
	virtual void UnitTick();

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitProperty")
		EUnitCamp m_UnitCamp = EUnitCamp::ENeatual;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UnitProperty")
		FUnitBaseAttribute m_BaseAttribute;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UnitProperty")
		TMap<class UBBuff*, int> m_ShieldMap;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UnitProperty")
		TArray<class UBBuff*> m_BuffList;

	EUnitLifeState m_UnitState = EUnitLifeState::EIdle;
	UINT8 m_UnitBuffState[(UINT8)EUnitBuffState::max] = { 0 };
	
private:
	float m_UnitTickCounter = 0.f;
};
