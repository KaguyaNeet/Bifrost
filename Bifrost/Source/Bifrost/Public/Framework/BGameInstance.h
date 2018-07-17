// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BIFROST_API UBGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	class ABUnitManager* GetUnitManager();
	class ABBuffManager* GetBuffManager();
private:
	class ABUnitManager* m_UnitManager = nullptr;
	class ABBuffManager* m_BuffManager = nullptr;
};
