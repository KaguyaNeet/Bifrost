// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BCard.generated.h"


enum class ECardFuncType
{
	Aura,
	EnableWeapon,
	DisableWeapon,
	DeathWords,
	BattleRoar,
	AttackEffects,
	PropertyIncrease,
	PropertyDecrease,
	EnableArmor,
	DisableArmor,
	LittleSpells,
	ProduceIncrease,
	ProduceDecrease,
	LargeSpells
};

UENUM(BlueprintType)
enum class ECardType : uint8
{
	ENone UMETA(DisplayName = "None"),
	EArmor UMETA(DisplayName = "Armor"),
	EWeapon UMETA(DisplayName = "Weapon"),
	EAura UMETA(DisplayName = "Aura"),
	EDeathWords UMETA(DisplayName = "DeathWords"),
	EBattleRoar UMETA(DisplayName = "BattleRoar"),
	EAttackEffects UMETA(DisplayName = "AttackEffects"),
	EPropertyIncrease UMETA(DisplayName = "PropertyIncrease"),
	ELittleSpells UMETA(DisplayName = "LittleSpells"),
	EBuilding UMETA(DisplayName = "Building"),
	ELargeSpells UMETA(DisplayName = "LargeSpells")
};

USTRUCT()
struct FCardAttribute : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		FName m_CardName;
	UPROPERTY(EditAnywhere)
		int m_CardKey;
	UPROPERTY(EditAnywhere)
		FString m_CardDescription;
	UPROPERTY(EditAnywhere)
		ECardType m_CardType;
	UPROPERTY(EditAnywhere)
		UTexture2D* m_CardTexture;
	UPROPERTY(EditAnywhere)
		UINT8 m_ProduceCardCost = 0;
	UPROPERTY(EditAnywhere)
		UINT8 m_UseCardCost = 0;
	UPROPERTY(EditAnywhere)
		UINT8 m_TickCardCost = 0;

	UPROPERTY(EditAnywhere)
		UParticleSystem* m_FireParticle = nullptr;
	UPROPERTY(EditAnywhere)
		UParticleSystem* m_OwnParticle = nullptr;
	UPROPERTY(EditAnywhere)
		UParticleSystem* m_HitParticle = nullptr;
	UPROPERTY(EditAnywhere)
		UParticleSystem* m_BulletParticle = nullptr;

	UPROPERTY(EditAnywhere)
		AActor* m_SpawnActor = nullptr;
};
/**
 * 
 */
UCLASS()
class BIFROST_API UBCard : public UObject
{
	GENERATED_BODY()
	
public:
	using CardFunc = void(*)(class ABUnit*, class ABUnit*, ECardFuncType);

public:
	void Initialize(const FCardAttribute& cardAttribute, CardFunc cardFunc);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FCardAttribute m_CardAttribute;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool m_Active = true;
	CardFunc m_CardFunction = nullptr;
	
	
};
