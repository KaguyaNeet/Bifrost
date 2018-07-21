// Fill out your copyright notice in the Description page of Project Settings.

#include "BCardManager.h"
#include "BUnit.h"

// Sets default values
ABCardManager::ABCardManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABCardManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABCardManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ABCardManager::CardFunc ABCardManager::GetFunction(int key)
{
	CardFunc result = nullptr;
	switch (key)
	{
		case 0:result = &CHOOSE_CARD_FUNCTION(TestCard);
	}
	return result;
}

CARD_FUNCTION_DEFINITION(TestCard)
{
	CHECK_CARD_TYPE(ECardFuncType::Aura);
}