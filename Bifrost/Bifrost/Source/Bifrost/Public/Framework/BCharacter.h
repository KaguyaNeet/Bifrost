// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/BUnit.h"
#include "BCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BIFROST_API ABCharacter : public ABUnit
{
	GENERATED_BODY()
	
public:
	ABCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	void MoveTo(FVector target);
	void MoveTo(AActor* target);

	void RVO2(float DeltaTime);

	UFUNCTION(BlueprintImplementableEvent)
		void Test(FVector a);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* target;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UCapsuleComponent* m_pCapsuleCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USkeletalMeshComponent* m_pCharacterMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UArrowComponent* m_pForwardArrow;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Property")
		FVector m_CurrentVelocity = FVector::ZeroVector;
	FVector m_CurrentAimVelocity = FVector::ZeroVector;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterProperty")
		float m_MaxMoveSpeed = 300;
	UPROPERTY(Category = EQS, EditAnywhere)
		FNavAgentProperties NavAgentProperties;

private:
	FVector m_MoveDirection = FVector::ZeroVector;
	FVector m_LastMoveDirection = FVector::ZeroVector;
	int currentPoint = 0;
	TArray<FNavPathPoint> path;
};
