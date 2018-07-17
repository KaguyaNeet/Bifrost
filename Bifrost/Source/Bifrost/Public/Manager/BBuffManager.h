// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BUnit.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BBuffManager.generated.h"



UCLASS()
class BIFROST_API ABBuffManager : public AActor
{
	GENERATED_BODY()
	
public:
	using BuffFunction = void(*)(ABUnit*, ABUnit*);

public:	
	// Sets default values for this actor's properties
	ABBuffManager();

	static ABBuffManager* GetBuffManager(AActor* caller);

	class UBBuff* CreateBuff(class ABUnit* owner, class ABUnit* adder, int buffKey);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void GetFunction(int key, BuffFunction& addFunction, BuffFunction& TickFunction, BuffFunction& RemoveFunction);

	
	
};

#define FUNCTION_DECLARATION(name) \
	namespace name \
	{ \
		static void Add##name(ABUnit* owner, ABUnit* adder); \
		static void Tick##name(ABUnit* owner, ABUnit* adder); \
		static void Remove##name(ABUnit* owner, ABUnit* adder); \
	}; \

#define ADD_FUNCTION_DEFINITION(name) \
	void BuffFunction::name::Add##name(ABUnit* owner, ABUnit* adder) \

#define TICK_FUNCTION_DEFINITION(name) \
	void BuffFunction::name::Tick##name(ABUnit* owner, ABUnit* adder) \

#define REMOVE_FUNCTION_DEFINITION(name) \
	void BuffFunction::name::Remove##name(ABUnit* owner, ABUnit* adder) \

#define CHOOSE_FUNCTION(name) \
	addFunction = &BuffFunction::##name##::Add##name; \
	TickFunction = &BuffFunction::##name##::Tick##name; \
	RemoveFunction = &BuffFunction::##name##::Remove##name; \

namespace BuffFunction
{
	FUNCTION_DECLARATION(TestFunction);
};