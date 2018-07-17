// Fill out your copyright notice in the Description page of Project Settings.

#include "BBuffManager.h"
#include "BGameInstance.h"
#include "BBuff.h"

// Sets default values
ABBuffManager::ABBuffManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

ABBuffManager * ABBuffManager::GetBuffManager(AActor * caller)
{
	if (UBGameInstance* gameInstance = Cast<UBGameInstance>(caller->GetGameInstance()))
	{
		return gameInstance->GetBuffManager();
	}
	else
	{
		return nullptr;
	}
}

UBBuff * ABBuffManager::CreateBuff(ABUnit * owner, ABUnit * adder, int buffKey)
{
	UBBuff* buff = NewObject<UBBuff>();

	BuffFunction addFunction;
	BuffFunction TickFunction;
	BuffFunction RemoveFunction;

	GetFunction(buffKey, addFunction, TickFunction, RemoveFunction);

	//buff->Initialize(owner, adder,)
	return nullptr;
}

// Called when the game starts or when spawned
void ABBuffManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABBuffManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABBuffManager::GetFunction(int key, BuffFunction& addFunction, BuffFunction& TickFunction, BuffFunction& RemoveFunction)
{
	switch (key)
	{
		case 0:CHOOSE_FUNCTION(TestFunction); break;
	}
}

ADD_FUNCTION_DEFINITION(TestFunction)
{

}
TICK_FUNCTION_DEFINITION(TestFunction)
{

}
REMOVE_FUNCTION_DEFINITION(TestFunction)
{

}