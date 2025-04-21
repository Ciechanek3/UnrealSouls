// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockOnComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnUpdatedTargetSignature,
	ULockOnComponent, OnUpdatedTargetDelegate,
	AActor*, NewTargetActorRef
);

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* CurrentTargetActor;

	UPROPERTY(BlueprintAssignable)
	FOnUpdatedTargetSignature OnUpdatedTargetDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void StartLockOn(float radius);
	void StopLockOn();

	UFUNCTION(BlueprintCallable)
	void ToggleLockOn(float radius);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	float _autoUnlockRange;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
