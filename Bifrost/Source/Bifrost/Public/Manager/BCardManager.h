// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BCard.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BCardManager.generated.h"

UCLASS()
class BIFROST_API ABCardManager : public AActor
{
	GENERATED_BODY()
	
public:
	using CardFunc = void(*)(class ABUnit*, class ABUnit*, ECardFuncType);

public:	
	// Sets default values for this actor's properties
	ABCardManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class BCard* CreateCard();

private:
	CardFunc GetFunction(int key);
	
};

#define CHECK_CARD_TYPE(value) \
	if(currentCalledType != value) \
		return; \

#define CHECK_CARD_TYPE_TWO_PARAMS(value1, value2) \
	if(currentCalledType != value1 && currentCalledType != value2) \
		return; \

#define CARD_FUNCTION_DECLARATION(name) \
	namespace name \
	{ \
		static void name##Func(class ABUnit* owner, class ABUnit* target, ECardFuncType currentCalledType); \
	}; \

#define CARD_FUNCTION_DEFINITION(name) \
	void CardFunction::name::name##Func(ABUnit* owner, ABUnit* target, ECardFuncType currentCalledType) \

#define CHOOSE_CARD_FUNCTION(name) \
	CardFunction::name::name##Func \

namespace CardFunction
{
	CARD_FUNCTION_DECLARATION(TestCard);
};