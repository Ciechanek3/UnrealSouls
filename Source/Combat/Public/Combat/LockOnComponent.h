// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockOnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBAT_API ULockOnComponent : public UActorComponent
{
	GENERATED_BODY()

	ACharacter* _ownerRef;

	APlayerController* _playerController;
	class UCharacterMovementComponent* _movementComp;

	class USpringArmComponent* _springArmComponent;

public:	
	// Sets default values for this component's properties
	ULockOnComponent();

	AActor* CurrentTargetActor;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void StartLockOn(float radius);
	void StopLockOn();

	UFUNCTION(BlueprintCallable)
	void ToggleLockOn(float radius = 750f);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
