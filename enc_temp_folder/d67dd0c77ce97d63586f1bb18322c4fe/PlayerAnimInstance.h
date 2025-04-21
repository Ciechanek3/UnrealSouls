// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class COMBAT_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float _currentSpeed { 0.0f };

	void UpdateSpeed();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsInCombat{ false };

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float _currentDirection { 0.0f };

public:

	UFUNCTION(BlueprintCallable)
	void HandleUpdateTarget(AActor* actor);

	UFUNCTION(BlueprintCallable)
	void UpdateDirection();
};
