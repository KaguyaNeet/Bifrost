// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BBuff.generated.h"

UENUM(BlueprintType)
enum class EBuffType : uint8
{
	ELifetime UMETA(DisplayName = "Lifetime"),
	EContinued UMETA(DisplayName = "Continued")
};

/**
 * 
 */
UCLASS()
class BIFROST_API UBBuff : public UObject
{
	GENERATED_BODY()
	
public:
	using AddBuffFunction = void(*)(class ABUnit*, class ABUnit*);
	using TickBuffFunction = void(*)(class ABUnit*, class ABUnit*);
	using RemoveBuffFunction = void(*)(class ABUnit*, class ABUnit*);
public:
	void Initialize(class ABUnit* owner, class ABUnit* adder, EBuffType buffType, int lifetime, int buffKey, AddBuffFunction addFunc, TickBuffFunction tickFunc, RemoveBuffFunction removeFunc);
	void AddBuff(class ABUnit* owner);
	void TickBuff(class ABUnit* owner);
	void RemoveBuff(class ABUnit* owner);
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int m_LifeTime = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int m_Key = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EBuffType m_BuffType;
private:
	class ABUnit* m_BuffAdder;

	AddBuffFunction m_AddBuffFunction;
	TickBuffFunction m_TickBuffFunction;
	RemoveBuffFunction m_RemoveBuffFunction;
};
