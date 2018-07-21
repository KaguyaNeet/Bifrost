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

};

UENUM(BlueprintType)
enum class ECardType : uint8
{
	EAura UMETA(DisplayName = "Aura"),
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
		UINT8 m_CardCost;
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
	void Initialize(int cardKey);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FName m_CardName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString m_CardDescription;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		ECardType m_CardType;
	CardFunc m_CardFunction = nullptr;
	
	
};
